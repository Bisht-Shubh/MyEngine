#include "pch.h"
#include "Camera.h"

void mouseCallBack(GLFWwindow* window, double xPos, double yPos);
	
void Camera::InitCamera()
{
	this->projection = glm::perspective(glm::radians(45.0f), (float)this->Width / (float)this->Height, 0.1f, 700.0f);
	this->view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

Camera::Camera(unsigned int Width, unsigned int Height, GLFWwindow* window)
	: Width(Width), Height(Height), window(window)
{
	InitCamera();
}

Camera::Camera()
	: Width(800), Height(600), window(nullptr)
{
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



