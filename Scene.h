#pragma once
#include<iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "MeshRenderer.h"
#include "Cube.h"
#include "Camera.h"
#include "Input.h"
#include "Transform.h"

class Scene
{
public:
	bool Keys[1024];
	bool KeysProcessed[1024];
	unsigned int Width, Height;

	Camera* camera;

	using UpdateCallback = std::function<void(Scene&, float)>;

	std::vector<MeshRenderer*> gameObjects;

	// Constructors
	Scene();
	Scene(unsigned int width, unsigned int height, Input& input);

	// Destructor
	~Scene();

	// Initialization
	void Init();

	// Game Loop
	void Update(float dt);
	void Render();

	// Client hooks
	void SetUpdateCallback(UpdateCallback callback);
	
	// Rendering
	Cube* Instantiate();

	void SetCamera(Camera* cam);
	Camera& GetCamera();

	// Set directional light properties and add to scene
	void SetDirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
	
	// Shadow mapping
	unsigned int depthMapFBO;
	unsigned int depthMap;
	unsigned int SHADOW_WIDTH = 2560, SHADOW_HEIGHT = 2560;
	void genDepthMap(unsigned int& depthMapFBO, unsigned int& depthMap, unsigned int SHADOW_WIDTH, unsigned int SHADOW_HEIGHT);
	

private:
	UpdateCallback updateCallback;

	Transform potTransform;

	// Frame timing
	float deltaTime{ 0.0f };
	float lastFrame{ 0.0f };

	Input& input;
};

