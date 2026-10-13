#include "pch.h"
#include "Game.h"

#include "Scene.h"
#include "Entity.h"
#include "MeshRenderer.h"
#include "Model.h"
#include "Material.h"
#include "Transform.h"
#include "SpotLight.h"
#include "ResourceManager.h"
#include "SceneSerializer.h"

Game::Game(Input& input)
    : m_input(input)
{
}

Game::~Game() = default;

void Game::Init()
{
    auto scene = std::make_unique<Scene>(1400, 1200, m_input);

    scene->Init();

    auto [it, inserted] = m_scenes.emplace("DefaultScene", std::move(scene));

    m_currentScene = it->second.get();
    
    CreateLevel();

	SceneSerializer::Deserialize(*m_currentScene, "Scene.json");
}

void Game::Update(float deltaTime)
{
    if (!m_currentScene)
        return;

    m_currentScene->Update(deltaTime);
}

void Game::LoadScene(const std::string& sceneName)
{
    auto it = m_scenes.find(sceneName);

    if (it == m_scenes.end())
    {
        std::cerr << "Scene not found: " << sceneName << std::endl;
        return;
    }

    m_currentScene = it->second.get();
}

Scene* Game::GetCurrentScene() const
{
    return m_currentScene;
}

void Game::CreateLevel()
{
    if (!m_currentScene)
        return;

    Entity bookStand = m_currentScene->CreateEntity("BookStand");

    MeshRenderer* meshRenderer = bookStand.AddComponent<MeshRenderer>();

    Model* bookStandModel = new Model("Assets/Models/Stand/scene.gltf");
    meshRenderer->SetModel(bookStandModel);

	Shader* shader = &ResourceManager::GetShader("SpotLight");

    Material* defaultMaterial = new Material(shader);
    meshRenderer->SetMaterial(defaultMaterial);

    Transform* bookStandTransform = bookStand.AddComponent<Transform>();
    bookStandTransform->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));

	SpotLight* spotLight1 = bookStand.AddComponent<SpotLight>();
	spotLight1->SetPosition(glm::vec3(0.0f, 15.0f, 0.0f));

	Entity car = m_currentScene->CreateEntity("Box");
	MeshRenderer* carMeshRenderer = car.AddComponent<MeshRenderer>();

	Model* carModel = new Model("Assets/Models/box/scene.gltf");
	carMeshRenderer->SetModel(carModel);
	carMeshRenderer->SetMaterial(defaultMaterial);
    
	Transform* carTransform = car.AddComponent<Transform>();
	carTransform->SetPosition(glm::vec3(-15.0f, 0.0f, 5.0f));

	SpotLight* spotLight2 = car.AddComponent<SpotLight>();
	spotLight2->SetPosition(glm::vec3(0.0f, 15.0f, 0.0f));
}