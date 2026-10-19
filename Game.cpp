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

#include <limits>
#include <glm/common.hpp>

Game::Game(Input& input)
    : m_input(input)
{
}

Game::~Game() = default;

void Game::Init()
{
    auto scene = std::make_unique<Scene>(2260, 1440, m_input);

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


    //float boundry = 5.0f;
    //float speed = 1.0f * deltaTime;
    //float rotationSpeed = 40.0f * deltaTime;

    //for(const EntityData& data : m_currentScene->GetEntityManager().GetAllEntities())
    //{
    //    glm::vec3& direction = m_directions.at(data.id);

    //    Entity entity = m_currentScene->GetEntityManager().GetEntity(data.id);
    //    Transform* transform = entity.GetComponent<Transform>();

    //    if (!transform)
    //        continue;

    //    if (transform->GetPosition().x >= boundry || transform->GetPosition().x <= -boundry)
    //        direction.x *= -1.0f;

    //    if (transform->GetPosition().y >= boundry || transform->GetPosition().y <= -boundry)
    //        direction.y *= -1.0f;

    //    if (transform->GetPosition().z >= boundry || transform->GetPosition().z <= -boundry)
    //        direction.z *= -1.0f;

    //    transform->Translate(direction.x * speed, direction.y * speed, direction.z * speed);
    //    transform->Rotate(rotationSpeed * 1.2f * direction.y, rotationSpeed * 0.2f * direction.z , rotationSpeed * 0.7f * direction.x);
    //}

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

    Shader* shader = &ResourceManager::GetShader("SpotLight");

    Material* defaultMaterial = new Material(shader);


    Model* molModel = new Model("Assets/Models/Water Molecule/Water Molecule.obj");

    Entity water = m_currentScene->CreateEntity("water");
    MeshRenderer* meshRenderer = water.AddComponent<MeshRenderer>();
    meshRenderer->SetModel(molModel);
    meshRenderer->SetMaterial(defaultMaterial);
    Transform* molTransform = water.AddComponent<Transform>();
    molTransform->SetPosition(glm::vec3((1.5), 0.0f, -2.0f ));

    SpotLight* spotLight1 = water.AddComponent<SpotLight>();
    spotLight1->SetPosition(glm::vec3(0.0f, 15.0f, 0.0f));


}