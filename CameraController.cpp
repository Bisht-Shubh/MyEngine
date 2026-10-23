#include "pch.h"
#include "CameraController.h"

void CameraController::Update(float deltaTime, Camera& camera, Input& input)
{
	// Update camera rotation and movement based on input
	if (!camera.IsCamDisabled())
	{
		if(input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
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

	// disable camera movement when cam disabled (e.g. when in editor mode)
	else if (camera.IsCamDisabled())
	{
		if(input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
			camera.Rotate(input.GetMouseXOffset(), input.GetMouseYOffset());

		input.ResetMouseDelta();
	}
}
