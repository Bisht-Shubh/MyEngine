#include "pch.h"
#include "Scene.h"

Scene::Scene(unsigned int width, unsigned int height, Input& input)
	: Width(width), Height(height), Keys(), input(input), camera(width, height, 45.0f)
{}

Scene::~Scene()
{}

//-------------------------------------------------------------------------------------------//
//------------------------------INITIALIZATION AND GAME LOOP----------------------------------//
//-------------------------------------------------------------------------------------------//

void Scene::Init()
{
    // Load models
	Car = std::make_unique<Model>("Assets/Models/Low Poly Car.obj");
    std::cout << "DEBUG::Car meshes: " << Car->meshes.size() << "\n";


    // Set properties of light
    glm::vec3 diffuse = glm::vec3(1.5f, 1.5f, 1.5f);
    glm::vec3 specular = glm::vec3(0.6f, 0.6f, 0.6f);
    glm::vec3 ambient = glm::vec3(1.6f, 1.6f, 1.6f);
	glm::vec3 pos = glm::vec3(0.0f, 12.0f, 0.0f);
	glm::vec3 dir = glm::vec3(0.0f, -1.0f, 0.0f);
	float innerAngle = 27.5f;  // degrees
	float outerAngle = 32.5f;  // degrees
 
	spotLight = std::make_unique<SpotLight>(ambient, diffuse, specular, pos, dir, innerAngle, outerAngle);
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
	ResourceManager::GetShader("SpotLight").Use().SetVector3f("viewPos", camera.GetCameraPos());
    if (spotLight == nullptr)
    {
        std::cerr << "Error: spotLight is a null pointer. Make sure it is initialized before calling Render()." << std::endl;
        return;
    }
	spotLight->ApplyLight(ResourceManager::GetShader("SpotLight").Use());
    
	ResourceManager::GetShader("SpotLight").Use().SetMatrix4("projection", camera.GetProjection());
	ResourceManager::GetShader("SpotLight").Use().SetMatrix4("view", camera.GetView());
	Car->Draw(ResourceManager::GetShader("SpotLight"));
}

void Scene::SetUpdateCallback(UpdateCallback callback)
{
    updateCallback = std::move(callback);
}

//void Scene::SetCamera(Camera cam)
//{
//	camera = cam
//}

Camera& Scene::GetCamera()
{
    return camera;
}

