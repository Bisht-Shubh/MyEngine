#pragma once

#include "pch.h"
#include "Engine.h"

void PrintShaderList();

Engine::Engine()
	: m_input(), m_window(1400, 1200, m_input)
{
	m_currentScene = std::make_unique<Scene>(m_window.GetWidth(), m_window.GetHeight(), m_input);
}

Engine::~Engine()
{
	m_currentScene.reset(nullptr);
}

void Engine::Init()
{
	m_window.InitWindow();
	LoadResources();
	m_currentScene->Init();
}

void Engine::LoadResources()
{   
	// Load time of shaders
	auto start = std::chrono::high_resolution_clock::now();

	//-------------------------------------------------------------------------------------------//
	//---------------------LOAD SHADERS AND PRINT LOAD TIME TO CONSOLE---------------------------//
	//-------------------------------------------------------------------------------------------//
	ResourceManager::LoadShader("Shader Files/SpotLight_vs.txt", "Shader Files/SpotLight_fs.txt", nullptr, "SpotLight");

	auto end = std::chrono::high_resolution_clock::now();       // END LOAD TIME

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << "\nDEBUG::Loaded shaders in::" << duration.count() << "ms";

	PrintShaderList();
}

void Engine::Run()
{
	GLFWwindow* window = m_window.GetWindow();

	Entity car = m_currentScene->CreateEntity("Car");
	MeshRenderer* meshRenderer = car.AddComponent<MeshRenderer>();

	Model carModel("Assets/Models/Low Poly Car.obj");
	meshRenderer->SetModel(&carModel);

	Material carMaterial(&ResourceManager::GetShader("SpotLight"));
	meshRenderer->SetMaterial(&carMaterial);

	Transform* carTransform = car.AddComponent<Transform>();
	carTransform->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));	

	SpotLight* spotlight = car.AddComponent<SpotLight>();

	// Game loop
	while (!m_window.ShouldClose())
	{
		glfwPollEvents();
		// Calculate delta time
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process input

		// Update 
		m_window.Update();
		m_cameraController.Update(deltaTime, m_currentScene->GetCamera(), m_input);
		m_renderer.Render(*m_currentScene);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		
	}
}

void Engine::LoadScene(Scene* newScene)
{
	if(m_currentScene)
		m_currentScene.reset(nullptr);

	m_currentScene = std::make_unique<Scene>(newScene->Width, newScene->Height, m_input);
	m_currentScene->Init();
}

Scene* Engine::GetCurrentScene() const
{
	return m_currentScene.get();
}

void PrintShaderList()
{
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
}
