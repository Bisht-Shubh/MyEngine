#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>


class Input;
class Scene;

class Game
{
public:

    explicit Game(Input& input);

    ~Game();

    void Init();
    void Update(float deltaTime);

    void LoadScene(
        const std::string& sceneName
    );

    Scene* GetCurrentScene() const;

    float GetTemperature()
    {
        return m_temperature;
    }

    void SetTemperature(float temp)
    {
        m_temperature = temp;
    }

private:

    void CreateLevel();

    // Temporary
    glm::vec3 m_boundry{2.0f, 5.0f, 2.0f};
    float m_temperature;

private:

    Input& m_input;

    std::unordered_map<
        std::string,
        std::unique_ptr<Scene>
    > m_scenes;

    std::unordered_map<unsigned int, glm::vec3> m_originalPositions;
    std::unordered_map<unsigned int, glm::vec3> m_directions;
    std::unordered_map<unsigned int, glm::vec3> m_originalRotations;
    std::unordered_map<unsigned int, bool> m_returningToBoundary;

    Scene* m_currentScene{ nullptr };
};