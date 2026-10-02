#include "pch.h"
#include "Scene.h"

Scene::Scene(unsigned int width, unsigned int height, Input& input)
	: Width(width), Height(height), Keys(), input(input), camera(width, height, 45.0f), m_entityManager(this), m_componentManager(this), m_spotLight(nullptr)
{
}

Scene::~Scene()
{}

//-------------------------------------------------------------------------------------------//
//------------------------------INITIALIZATION AND GAME LOOP----------------------------------//
//-------------------------------------------------------------------------------------------//

void Scene::Init()
{
    
}

//-------------------------------------------------------------------------------------------//
//------------------------------INPUT, UPDATE AND RENDERING----------------------------------//
//-------------------------------------------------------------------------------------------//


void Scene::Update(float dt)
{
	m_cameraController.Update(dt, camera, input);
}

void Scene::Render()
{
    // Screen details
    glViewport(0, 0, Width, Height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

Entity Scene::CreateEntity(const std::string& name)
{
    return m_entityManager.CreateEntity(name);
}

EntityManager& Scene::GetEntityManager()
{
    return m_entityManager;
}


ComponentManager& Scene::GetComponentManager()
{
	return m_componentManager;
}

