#pragma once

#include "Scene.h"
#include<memory>

class Engine
{
private:
	Scene* currentScene;
	float deltaTime{ 0.0f };
	float lastFrame{ 0.0f };

public:
	// Constructor
	Engine(unsigned int width, unsigned int height);

	// Destructor
	~Engine();

	// Prevent copying and ensure move semantics
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	// Initialization
	void Init();

	// Main game loop
	void Run();

	// Scene management
	void LoadScene(Scene* newScene);
	Scene* GetCurrentScene() const;
};

