#include "pch.h"
#include "CameraController.h"

void CameraController::Update(float deltaTime, Camera& camera, Input& input)
{
	camera.Rotate(input.GetMouseXOffset(), input.GetMouseYOffset());

	input.ResetMouseDelta();

	if (input.IsKeyPressed(GLFW_KEY_W))
	{
		camera.MoveForward(deltaTime);
	}

	if (input.IsKeyPressed(GLFW_KEY_S))
	{
		camera.MoveBackward(deltaTime);
	}

	if (input.IsKeyPressed(GLFW_KEY_A))
	{
		camera.MoveLeft(deltaTime);
	}

	if (input.IsKeyPressed(GLFW_KEY_D))
	{
		camera.MoveRight(deltaTime);
	}

	if (input.IsKeyPressed(GLFW_KEY_SPACE))
	{
		camera.MoveUp(deltaTime);
	}

	if (input.IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
	{
		camera.MoveDown(deltaTime);
	}
}
