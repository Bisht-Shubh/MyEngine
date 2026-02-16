#pragma once

#include "pch.h"
#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height)
	: currentScene(nullptr), deltaTime(0.0f), lastFrame(0.0f)
{
	currentScene = new Scene(width, height);
}

Engine::~Engine()
{
	delete currentScene;
}

void Engine::Init()
{
	currentScene->Init();
}

void Engine::Run()
{
	GLFWwindow* window = currentScene->GetWindow();

	// Game loop
	while (!currentScene->ShouldClose(window))
	{
		// Calculate delta time
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process input
		currentScene->ProcessInput(deltaTime);

		// Update 
		currentScene->Update(deltaTime);
		
		// Render
		currentScene->Render();

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Engine::LoadScene(Scene* newScene)
{
	if(currentScene)
		delete currentScene;

	currentScene = newScene;
	currentScene->Init();
}

Scene* Engine::GetCurrentScene() const
{
	return currentScene;
}


