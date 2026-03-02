///CAMERA CLASS

#pragma once

#define GLM_ENABLE_EXPERIMENTAL


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Camera
{
private:
	glm::vec3 cameraPos{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 cameraFront{ glm::vec3(0.0f, 0.0f, -1.0f) };
	glm::vec3 cameraUp{ glm::vec3(0.0f, 1.0f, 0.0f) };
	const float radius{ 10.0f };
	const float cameraSpeed{ 12.5f };
	const float FOV{ 45.0f };			// Set 45.0f as default FOV, can be changed in constructor
	
	GLFWwindow* window;

public:
	unsigned int Width, Height;

	/*Nearest and farthest distances that player/camera can see
	Set to default, can be changed by client*/
	float nearPlane{ 0.1f };
	float farPlane{ 700.0f };

	// Camera attributes
	glm::mat4 view;
	glm::mat4 projection{ glm::mat4{1.0f} };

	// Initialse Camera
	void InitCamera();

	// Constructor
	Camera(unsigned int windowWidth, unsigned int windowHeight, float cameraFOV, GLFWwindow* window);
	Camera();

	// Getters
	glm::mat4 GetView();
	glm::mat4 GetProjection();
	glm::vec3 GetCameraPos();
	glm::vec3 GetCameraFront();
	glm::vec3 GetCameraUp();
	float GetCameraSpeed();

	// Setters
	void SetCameraPos(glm::vec3 pos);
	void SetCameraFront(glm::vec3 front);
	void SetCameraUp(glm::vec3 up);
};

