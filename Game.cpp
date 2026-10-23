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
#include <cmath>


Game::Game(Input& input)
    : m_input(input)
{
}

Game::~Game() = default;

void Game::Init()
{
    auto scene = std::make_unique<Scene>(2560, 1440, m_input);

    scene->Init();

    auto [it, inserted] = m_scenes.emplace("DefaultScene", std::move(scene));

    m_currentScene = it->second.get();
    
    CreateLevel();

	SceneSerializer::Deserialize(*m_currentScene, "Scene.json");

    for (const EntityData& data : m_currentScene->GetEntityManager().GetAllEntities())
    {
        Entity entity = m_currentScene->GetEntityManager().GetEntity(data.id);

        Transform* transform = entity.GetComponent<Transform>();
        if (transform)
        {
            m_originalPositions[data.id] = transform->GetPosition();
            m_originalRotations[data.id] = transform->GetRotation();
        }
    }
}

void Game::Update(float deltaTime)
{
    if (!m_currentScene)
        return;

    
    float speed = 4.0f * deltaTime;
    float rotationSpeed = 80.0f * deltaTime;
    const float amplitude = 0.01f;
    const float frequency = 30.0f;
    float time = glfwGetTime();

    glm::vec3 offset(amplitude * sin(frequency * time), amplitude * sin(frequency * time * 1.3f), 0.0f);

    for (const EntityData& data : m_currentScene->GetEntityManager().GetAllEntities())
    {
        
        Entity entity = m_currentScene->GetEntityManager().GetEntity(data.id);

        Transform* transform = entity.GetComponent<Transform>();
        if (!transform)
            continue;

        glm::vec3 originalPos = transform->GetPosition();
       
        if (m_temperature <= 0.0f)
        {
            const glm::vec3 target = m_originalPositions.at(data.id);
            const glm::vec3 current = transform->GetPosition();
            const glm::vec3 difference = target - current;

            glm::vec3 currentRotation = transform->GetRotation();
            glm::vec3 targetRotation = m_originalRotations.at(data.id);

            const float distance = glm::length(difference);
            const float returnSpeed = 4.0f;
            const float step = returnSpeed * deltaTime;

            if (distance > step)
            {
                transform->SetPosition(current + (difference / distance) * step);
                float t = glm::clamp(returnSpeed * deltaTime, 0.0f, 1.0f);
                transform->SetRotation(glm::mix(transform->GetRotation(), m_originalRotations.at(data.id), t));
            }
            else
                transform->SetPosition(originalPos + offset);
        }
        else
        {
            glm::vec3 position = transform->GetPosition();
            glm::vec3& direction = m_directions.at(data.id);

            if (m_temperature < 4.0f)
                m_boundry = glm::vec3(6.0f, 6.0f, 6.0f);
            else
                m_boundry = glm::vec3(2.0f, 4.0f, 2.0f);

            glm::vec3 target = glm::clamp(position, -m_boundry, m_boundry);
            glm::vec3 difference = target - position;
            float distance = glm::length(difference);

            const float returnSpeed = 6.0f;
            const float step = returnSpeed * deltaTime;

            if (distance > 0.0001f)
            {
                if (distance > step)
                    transform->SetPosition(position + (difference / distance) * step);

                else
                {
                    transform->SetPosition(target);

                    if (position.x > m_boundry.x)
                        direction.x = -std::abs(direction.x);
                    else if (position.x < -m_boundry.x)
                        direction.x = std::abs(direction.x);

                    if (position.y > m_boundry.y)
                        direction.y = -std::abs(direction.y);
                    else if (position.y < -m_boundry.y)
                        direction.y = std::abs(direction.y);

                    if (position.z > m_boundry.z)
                        direction.z = -std::abs(direction.z);
                    else if (position.z < -m_boundry.z)
                        direction.z = std::abs(direction.z);
                }

                transform->Rotate(rotationSpeed * 1.2f * direction.y, rotationSpeed * 0.2f * direction.z, rotationSpeed * 0.7f * direction.x);

                continue;
            }

            // Already inside the boundary: move freely.
            transform->Translate(direction.x * speed, direction.y * speed, direction.z * speed);
            glm::vec3 newPosition = transform->GetPosition();

            if (newPosition.x > m_boundry.x)
                direction.x = -std::abs(direction.x);
            else if (newPosition.x < -m_boundry.x)
                direction.x = std::abs(direction.x);

            if (newPosition.y > m_boundry.y)
                direction.y = -std::abs(direction.y);
            else if (newPosition.y < -m_boundry.y)
                direction.y = std::abs(direction.y);

            if (newPosition.z > m_boundry.z)
                direction.z = -std::abs(direction.z);
            else if (newPosition.z < -m_boundry.z)
                direction.z = std::abs(direction.z);

            transform->Rotate(rotationSpeed * 1.2f * direction.y, rotationSpeed * 0.2f * direction.z, rotationSpeed * 0.7f * direction.x);
        }
    }

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

    Model* molModel = new Model("Assets/Models/box/scene.gltf");

    for (int i = 0; i < 6; i++)
    {
        Entity water = m_currentScene->CreateEntity("water");
        MeshRenderer* meshRenderer = water.AddComponent<MeshRenderer>();
        meshRenderer->SetModel(molModel);
        meshRenderer->SetMaterial(defaultMaterial);
        Transform* molTransform = water.AddComponent<Transform>();

        if (i < 1)
        {
            SpotLight* spotLight1 = water.AddComponent<SpotLight>();
            spotLight1->SetPosition(glm::vec3(0.0f, 15.0f, 0.0f));
        }
        m_directions[water.GetID()] = glm::vec3(1 + (0.3f * i), 1 + (-0.7f * i), 1 + (1.4 * i));
    }

}
