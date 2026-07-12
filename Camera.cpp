#include "pch.h"
#include "Camera.h"
	
void Camera::UpdateCameraVectors()
{
	cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront.y = sin(glm::radians(pitch));
	cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(cameraFront);

	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));

	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void Camera::InitCamera()
{
	this->projection = glm::perspective(glm::radians(FOV), (float)this->Width / (float)this->Height, nearPlane, farPlane);
	this->view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

Camera::Camera(unsigned int windowWidth, unsigned int windowHeight, float cameraFOV)
	: Width(windowWidth), Height(windowHeight), FOV(cameraFOV)
{
	InitCamera();
}

Camera::Camera()
	: Width(800), Height(600), FOV(45.0f)
{
}

void Camera::Rotate(float xOffset, float yOffset)
{
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	UpdateCameraVectors();
}

//--------------------------------------------------------------------------//
//-------------------------------MOVEMENT-----------------------------------//
//--------------------------------------------------------------------------//

void Camera::MoveForward(float deltaTime)
{
	cameraPos += cameraSpeed * deltaTime * cameraFront;
}

void Camera::MoveBackward(float deltaTime)
{
	cameraPos -= cameraSpeed * deltaTime * cameraFront;
}

void Camera::MoveLeft(float deltaTime)
{
	cameraPos -= cameraSpeed * deltaTime * cameraRight;
}

void Camera::MoveRight(float deltaTime)
{
	cameraPos += cameraSpeed * deltaTime * cameraRight;
}

void Camera::MoveUp(float deltaTime)
{
	cameraPos += cameraSpeed * deltaTime * cameraUp;
}

void Camera::MoveDown(float deltaTime)
{
	cameraPos -= cameraSpeed * deltaTime * cameraUp;
}

//--------------------------------------------------------------------------
//---------------------------------GETTERS----------------------------------
//--------------------------------------------------------------------------

glm::mat4 Camera::GetView()
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	return view;
}

glm::mat4 Camera::GetProjection()
{
	return projection;
}

glm::vec3 Camera::GetCameraPos()
{
	return cameraPos;
}

glm::vec3 Camera::GetCameraFront()
{
	return cameraFront;
}

glm::vec3 Camera::GetCameraUp()
{
	return cameraUp;
}

float Camera::GetCameraSpeed()
{
	return cameraSpeed;
}

//--------------------------------------------------------------------------
//---------------------------------SETTERS----------------------------------
//--------------------------------------------------------------------------

void Camera::SetCameraPos(glm::vec3 pos)
{
	cameraPos = pos;
}

void Camera::SetCameraFront(glm::vec3 front)
{
	cameraFront = front;
}

void Camera::SetCameraUp(glm::vec3 up)
{
	cameraUp = up;
}



