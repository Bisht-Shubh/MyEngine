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

#include<chrono>

// LIGHTING
PointLight* pointLight;

// MODELS
Model* Table;

Scene::Scene(unsigned int width, unsigned int height, Input& input)
	: Width(width), Height(height), Keys(), input(input)  
{

}

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
	ResourceManager::LoadShader("D:/OpenGL/MyEngine/PointLightTest_vs.txt", "D:/OpenGL/MyEngine/PointLightTest_fs.txt", nullptr, "PointLight");

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
	Table = new Model("D:/Assets/Blender Files/LowPolyTree.obj");
    std::cout << "DEBUG::Table meshes: " << Table->meshes.size() << "\n";


    // Set properties of light
    glm::vec3 diffuse = glm::vec3(2.0f, 1.9f, 1.98f);
    glm::vec3 specular = glm::vec3(0.7f, 0.5f, 0.35f);
    glm::vec3 ambient = glm::vec3(0.4f, 0.4f, 0.39f);
	glm::vec3 pos = glm::vec3(0.0f, 9.0f, 0.0f);
	float intensity = 3.0f;

	pointLight = new PointLight(ambient, diffuse, specular, pos, intensity);
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
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	ResourceManager::GetShader("PointLight").Use().SetMatrix4("model", model);
	ResourceManager::GetShader("PointLight").Use().SetVector3f("viewPos", camera->GetCameraPos());
    if (pointLight == nullptr)
    {
        std::cerr << "Error: pointLight is a null pointer. Make sure it is initialized before calling Render()." << std::endl;
        return;
    }
	pointLight->ApplyLight(ResourceManager::GetShader("PointLight").Use());
    
	ResourceManager::GetShader("PointLight").Use().SetMatrix4("projection", camera->GetProjection());
	ResourceManager::GetShader("PointLight").Use().SetMatrix4("view", camera->GetView());
	Table->Draw(ResourceManager::GetShader("PointLight"));

	model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(7.0f, 9.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
    ResourceManager::GetShader("PointLight").Use().SetMatrix4("model", model);
	Table->Draw(ResourceManager::GetShader("PointLight"));

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-8.0f, 11.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ResourceManager::GetShader("PointLight").Use().SetMatrix4("model", model);
	Table->Draw(ResourceManager::GetShader("PointLight"));

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 14.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
    ResourceManager::GetShader("PointLight").Use().SetMatrix4("model", model);
    Table->Draw(ResourceManager::GetShader("PointLight"));
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

