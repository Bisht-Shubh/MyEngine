#pragma once
#include<iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "MeshRenderer.h"
#include "Cube.h"
#include "Camera.h"

class Scene
{
public:
	bool Keys[1024];
	bool KeysProcessed[1024];
	unsigned int Width, Height;

	using UpdateCallback = std::function<void(Scene&, float)>;

	std::vector<MeshRenderer*> gameObjects;

	// Constructors
	Scene();
	Scene(unsigned int width, unsigned int height);

	// Destructor
	~Scene();

	// Initialization
	void Init();

	// Game Loop
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	// Client hooks
	void SetUpdateCallback(UpdateCallback callback);
	
	// Get window
	void InitWindow();
	GLFWwindow* GetWindow() const;

	// Close application
	bool ShouldClose(GLFWwindow* window);

	// Rendering
	Cube* Instantiate();

	void SetCamera(Camera* cam);

private:
	UpdateCallback updateCallback;

	// Frame timing
	float deltaTime{ 0.0f };
	float lastFrame{ 0.0f };

	// GLFW window and input
	GLFWwindow* window;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	Camera* camera;

	static void mouseCallBack(GLFWwindow* window, double xPos, double yPos);
	void mouseMovement(float xOffset, float yOffset);
};

