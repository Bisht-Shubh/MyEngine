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

Game::Game(Input& input)
    : m_input(input)
{
}

Game::~Game() = default;

void Game::Init()
{
    auto scene =
        std::make_unique<Scene>(
            1400,
            1200,
            m_input
        );

    scene->Init();

    auto [it, inserted] =
        m_scenes.emplace(
            "DefaultScene",
            std::move(scene)
        );

    m_currentScene =
        it->second.get();

    CreateLevel();
}

void Game::Update(float deltaTime)
{
    if (!m_currentScene)
        return;

    m_currentScene->Update(deltaTime);
}

void Game::LoadScene(
    const std::string& sceneName
)
{
    auto it =
        m_scenes.find(sceneName);

    if (it == m_scenes.end())
    {
        std::cerr
            << "Scene not found: "
            << sceneName
            << std::endl;

        return;
    }

    m_currentScene =
        it->second.get();
}

Scene* Game::GetCurrentScene() const
{
    return m_currentScene;
}

void Game::CreateLevel()
{
    if (!m_currentScene)
        return;

    Entity car =
        m_currentScene->CreateEntity("Car");

    MeshRenderer* meshRenderer =
        car.AddComponent<MeshRenderer>();

    Model* carModel =
        new Model(
            "Assets/Models/Low Poly Car.obj"
        );

    meshRenderer->SetModel(carModel);

    Material* carMaterial =
        new Material(
            &ResourceManager::GetShader("SpotLight")
        );

    meshRenderer->SetMaterial(carMaterial);

    Transform* carTransform =
        car.AddComponent<Transform>();

    carTransform->SetPosition(
        glm::vec3(
            0.0f,
            0.0f,
            -5.0f
        )
    );

    car.AddComponent<SpotLight>();
}