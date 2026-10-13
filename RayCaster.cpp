#include "pch.h"
#include "RayCaster.h"

#include <algorithm>
#include <limits>
#include <cmath>

Ray RayCaster::CreateRay(float mouseX, float mouseY, int screenWidth, int screenHeight, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 cameraPosition)
{
	// Create mouse viewport coords to Normalized Device Coordinates (NDC)
	float x = (2.0f * mouseX) / screenWidth - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / screenHeight;
	float z = 1.0f;		
	glm::vec3 rayNDC = glm::vec3(x, y, z);

	// Convert NDC to clip space
	glm::vec4 rayClip = glm::vec4(rayNDC.x, rayNDC.y, -1.0f, 1.0f);			// Point ray z direction forward	

	// Convert clip space to eye space / Cam coords
	glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;			// multiply by inverse projection matrix
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);					// set z to -1 and w to 0 -> this is a direction vector

	// Convert eye space to world space
	glm::vec3 rayWorld = glm::vec3(glm::inverse(viewMatrix) * rayEye);	// multiply by inverse view matrix
	rayWorld = glm::normalize(rayWorld);	// normalize the direction vector

    return Ray(cameraPosition, rayWorld);
}

bool RayCaster::IntersectsAABB(const Ray& ray, const glm::vec3& boundsMin, const glm::vec3& boundsMax, float& hitDistance)
{
	float tMin = 0.0f;
    float tMax = std::numeric_limits<float>::max();

    for (int axis = 0; axis < 3; ++axis)
    {
        float origin = ray.origin[axis];
        float direction = ray.direction[axis];

        // Ray parallel to this pair of box planes
        if (std::abs(direction) < 1e-8f)
        {
            if (origin < boundsMin[axis] ||
                origin > boundsMax[axis])
            {
                return false;
            }

            continue;
        }

        float t1 = (boundsMin[axis] - origin) / direction;
        float t2 = (boundsMax[axis] - origin) / direction;

        if (t1 > t2)
            std::swap(t1, t2);

        tMin = std::max(tMin, t1);
        tMax = std::min(tMax, t2);

        // No overlapping interval: no intersection
        if (tMin > tMax)
            return false;
    }

    hitDistance = tMin;
	
    return true;
}
