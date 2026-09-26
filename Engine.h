#pragma once

#include "Scene.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "DirectionalLight.h"
#include "ResourceManager.h"
#include "Input.h"
#include "CameraController.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Material.h"
#include "Renderer.h"
#include "DebugLayer.h"

#include <chrono>
#include <memory>

class Engine
{
private:
    std::unique_ptr<Scene> m_currentScene;

    Input& m_input;

    CameraController m_cameraController;
    Renderer m_renderer;
    DebugLayer m_debugLayer;

public:
    explicit Engine(Input& input);
    ~Engine();

    // Prevent copying
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    // Engine initialization
    void Init();
    void LoadResources();

    // Per-frame engine operations
    void Update(float deltaTime);
    void Render();

    // Scene management
    void LoadScene(Scene* newScene);
    Scene* GetCurrentScene() const;

    // Debug information
    DebugLayer& GetDebugLayer();
};