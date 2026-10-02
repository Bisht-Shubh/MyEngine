#pragma once

#include <memory>
#include <unordered_map>
#include <string>

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

private:

    void CreateLevel();

private:

    Input& m_input;

    std::unordered_map<
        std::string,
        std::unique_ptr<Scene>
    > m_scenes;

    Scene* m_currentScene{ nullptr };
};