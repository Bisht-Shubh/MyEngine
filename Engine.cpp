#pragma once

#include "pch.h"
#include "Engine.h"


Engine::Engine()
	: m_input(), m_window(1000, 1200, m_input)
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

	m_currentScene->Init();
}

void Engine::Run()
{
	GLFWwindow* window = m_window.GetWindow();

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
		m_currentScene->Update(deltaTime);
		
		// Render
		m_currentScene->Render();

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


