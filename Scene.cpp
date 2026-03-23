#include "pch.h"
#include "Scene.h"

#include "ResourceManager.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Cube.h"

MeshRenderer* gameObject;

Cube* cube;

Scene::Scene(unsigned int width, unsigned int height)
	: Width(width), Height(height), Keys()
{

}

Scene::~Scene()
{
    glfwTerminate();
}

void Scene::Init()
{
    // Initialise window
    InitWindow();

    glfwSetWindowUserPointer(this->window, this);
    glfwSetCursorPosCallback(this->window, Scene::mouseCallBack);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Load shaders
	ResourceManager::LoadShader("D:/OpenGL/MyEngine/Mesh_vs.txt", "D:/OpenGL/MyEngine/Mesh_fs.txt", nullptr, "cube");

	// Initialize game objects
	
}

void Scene::ProcessInput(float dt)
{
	if(this->Keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(this->window, true);

    // Camera controls

        // Set Camera Constraints
    glm::vec3 cameraPos = camera->GetCameraPos();
    glm::vec3 cameraFront = camera->GetCameraFront();
    glm::vec3 cameraUp = camera->GetCameraUp();
    float cameraSpeed = camera->GetCameraSpeed();

    // Move Forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * dt * cameraFront;

    // Move Backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * dt * cameraFront;

    // Move Left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;

    // Move Right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;

    // Update Camera Position
    camera->SetCameraPos(cameraPos);
    camera->SetCameraFront(cameraFront);
    camera->SetCameraUp(cameraUp);
}

void Scene::Update(float dt)
{
    if (updateCallback)
        updateCallback(*this, dt);
}

void Scene::Render()
{
    // Screen details
    glViewport(0, 0, Width, Height);
    glClearColor(0.5f, 0.7f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (MeshRenderer* obj : gameObjects)
    {
        obj->SetViewProjection(camera->GetView(), camera->GetProjection());
        obj->DrawMesh();
    }

	//cube->SetViewProjection(camera->GetView(), camera->GetProjection());
    //cube->DrawMesh();
}

void Scene::SetUpdateCallback(UpdateCallback callback)
{
    updateCallback = std::move(callback);
}

void Scene::InitWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    window = glfwCreateWindow(Width, Height, "Scene", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "\nFailed to create window, exiting!";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, Scene::key_callback);
    glfwSetWindowUserPointer(window, this);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "\nFailed to initialise GLAD!";
        std::exit(EXIT_FAILURE);
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);   
	glDepthFunc(GL_LESS);   
}

GLFWwindow* Scene::GetWindow() const
{
    return window;
}

bool Scene::ShouldClose(GLFWwindow* window)
{
    if(glfwWindowShouldClose(window))
		return true;
}

// Add a new game object to the scene with each Instantiate call in main.cpp
// TODO : Add functionality to specify which type of game object to instantiate (e.g. cube, sphere, cuboid, etc)
// And remove return functionality
Cube* Scene::Instantiate()
{
	Shader& cubeShader = ResourceManager::GetShader("cube");
    cube = new Cube(cubeShader, Width, Height);
    gameObjects.push_back(cube);
    return cube;
}

void Scene::SetCamera(Camera* cam)
{
	camera = cam;
}

void Scene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Scene::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
    if (scene && key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            scene->Keys[key] = true;
        else if (action == GLFW_RELEASE)
        {
            scene->Keys[key] = false;
            scene->KeysProcessed[key] = false;
        }
    }
}

struct mouseInput {
    double lastX = 1800.0f / 2.0f;
    double lastY = 1000.0f / 2.0f;
    bool firstMouse{ true };
    double xOffset{ 0.0f };
    double yOffset{ 0.0f };
} mouseInput;

void Scene::mouseCallBack(GLFWwindow* window, double xPos, double yPos)
{
    Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
    Camera* camera = scene->camera;
    if (mouseInput.firstMouse)
    {
        mouseInput.lastX = xPos;
        mouseInput.lastY = yPos;
        mouseInput.firstMouse = false;
    }

    mouseInput.xOffset = xPos - mouseInput.lastX;
    mouseInput.yOffset = mouseInput.lastY - yPos;
    mouseInput.lastX = xPos;
    mouseInput.lastY = yPos;
    scene->mouseMovement(mouseInput.xOffset, mouseInput.yOffset);
}

void Scene::mouseMovement(float xOffset, float yOffset)
{
    static float yaw = -90.0f;
    static float pitch = 0.0f;
    float camSenstivity{ 0.1f };

    xOffset *= camSenstivity;
    yOffset *= camSenstivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);

    camera->SetCameraFront(direction);
}

