#pragma once

#include "Scene.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Cube.h"
#include "DirectionalLight.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Input.h"
#include "CameraController.h"

#include<chrono>
#include<memory>

class Engine
{
private:
	std::unique_ptr<Scene> m_currentScene;
	float deltaTime{ 0.0f };
	float lastFrame{ 0.0f };

	Input m_input;
	Window m_window;
	CameraController m_cameraController;

public:
	Engine();

	~Engine();

	// Prevent copying and ensure move semantics
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void Init();
	void LoadResources();

	void Run();

	// Scene management
	void LoadScene(Scene* newScene);
	Scene* GetCurrentScene() const;
};

