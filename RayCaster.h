#pragma once
#include <glm/glm.hpp>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;
};

class RayCaster
{
public:
	static Ray CreateRay(float mouseX, float mouseY, int screenWidth, int screenHeight,
								const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 cameraPosition);

	static bool IntersectsAABB(const Ray& ray, const glm::vec3& boundsMin, const glm::vec3& boundsMax, float& hitDistance);
};
