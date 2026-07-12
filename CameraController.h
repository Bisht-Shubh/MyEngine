#pragma once
#include "Camera.h"
#include "Input.h"

class CameraController
{
public:
	void Update(float deltaTime, Camera& camera, Input& input);
};

