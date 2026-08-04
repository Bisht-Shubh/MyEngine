#include "pch.h"
#include "Scene.h"

#include "ResourceManager.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Cube.h"
#include "Model.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "Window.h"
#include "PointLight.h"
#include "SpotLight.h"

#include<chrono>

// LIGHTING
SpotLight* spotLight;

// MODELS
Model* Car;

Scene::Scene(unsigned int width, unsigned int height, Input& input)
    : Width(width), Height(height), Keys(), input(input)
{}

Scene::~Scene()
{
    glfwTerminate();
}

//-------------------------------------------------------------------------------------------//
//------------------------------INITIALIZATION AND GAME LOOP----------------------------------//
//-------------------------------------------------------------------------------------------//

void Scene::Init()
{
	camera = new Camera(Width, Height, 45.0f);

    // Load time of shaders
    auto start = std::chrono::high_resolution_clock::now();

    //-------------------------------------------------------------------------------------------//
	//---------------------LOAD SHADERS AND PRINT LOAD TIME TO CONSOLE---------------------------//
	//-------------------------------------------------------------------------------------------//
	ResourceManager::LoadShader("D:/OpenGL/MyEngine/SpotLight_vs.txt", "D:/OpenGL/MyEngine/SpotLight_fs.txt", nullptr, "SpotLight");

    auto end = std::chrono::high_resolution_clock::now();       // END LOAD TIME

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\nDEBUG::Loaded shaders in::" << duration.count() << "ms";

    // List loaded shaders
    std::stringstream ss;

    ss << "\n============================================\n";
    ss << "DEBUG::Shader loading complete";
    ss << "\nLOADED_SHADERS::(" << ResourceManager::Shaders.size() << ")\n";    // print total shaders loaded
    ss << "\n--------------------------------------------\n";

    for (const auto& [name, shader] : ResourceManager::Shaders)
        ss << name << "\n";                         // print all shaders name

    ss << "============================================\n";

    std::cout << ss.str();

    // Load models
	Car = new Model("D:/Assets/Blender Files/Low Poly Car.obj");
    std::cout << "DEBUG::Car meshes: " << Car->meshes.size() << "\n";


    // Set properties of light
    glm::vec3 diffuse = glm::vec3(1.5f, 1.5f, 1.5f);
    glm::vec3 specular = glm::vec3(0.6f, 0.6f, 0.6f);
    glm::vec3 ambient = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 pos = glm::vec3(0.0f, 13.0f, 0.0f);
	glm::vec3 dir = glm::vec3(0.0f, -1.0f, 0.0f);
	float innerAngle = 12.5f;  // degrees
	float outerAngle = 17.5f;  // degrees

	spotLight = new SpotLight(ambient, diffuse, specular, pos, dir, innerAngle, outerAngle);
	spotLight->SetIntensity(2.6f);
}

//-------------------------------------------------------------------------------------------//
//------------------------------INPUT, UPDATE AND RENDERING----------------------------------//
//-------------------------------------------------------------------------------------------//


void Scene::Update(float dt)
{

}

void Scene::Render()
{
    // Screen details
    glViewport(0, 0, Width, Height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	ResourceManager::GetShader("SpotLight").Use().SetMatrix4("model", model);
	ResourceManager::GetShader("SpotLight").Use().SetVector3f("viewPos", camera->GetCameraPos());
    if (spotLight == nullptr)
    {
        std::cerr << "Error: spotLight is a null pointer. Make sure it is initialized before calling Render()." << std::endl;
        return;
    }
	spotLight->ApplyLight(ResourceManager::GetShader("SpotLight").Use());
    
	ResourceManager::GetShader("SpotLight").Use().SetMatrix4("projection", camera->GetProjection());
	ResourceManager::GetShader("SpotLight").Use().SetMatrix4("view", camera->GetView());
	Car->Draw(ResourceManager::GetShader("SpotLight"));
}

void Scene::SetUpdateCallback(UpdateCallback callback)
{
    updateCallback = std::move(callback);
}

//--------------------------------------------------------------------------------------------//
//-----------------------------WINDOW INITIALIZATION AND INPUT CALLBACKS----------------------//
//-------------------------------------------------------------------------------------------//

void Scene::SetCamera(Camera* cam)
{
	camera = cam;
}

Camera& Scene::GetCamera()
{
    return *camera;
}

