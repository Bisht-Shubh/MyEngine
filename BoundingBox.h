#pragma once

#include <glm/glm.hpp>
#include <limits>

struct BoundingBox {
	glm::vec3 minPoint;
	glm::vec3 maxPoint;
};

inline BoundingBox TransformBoundingBox(
    const BoundingBox& localBounds,
    const glm::mat4& modelMatrix)
{
    BoundingBox worldBounds{
        glm::vec3((std::numeric_limits<float>::max)()),
        glm::vec3(std::numeric_limits<float>::lowest())
    };

    for (int i = 0; i < 8; ++i)
    {
        glm::vec3 corner((i & 1) ? localBounds.maxPoint.x : localBounds.minPoint.x, (i & 2) ? localBounds.maxPoint.y : localBounds.minPoint.y, (i & 4) ? localBounds.maxPoint.z : localBounds.minPoint.z);

        glm::vec3 worldCorner = glm::vec3(modelMatrix * glm::vec4(corner, 1.0f));

        worldBounds.minPoint = (glm::min)(worldBounds.minPoint, worldCorner);
        worldBounds.maxPoint = (glm::max)(worldBounds.maxPoint, worldCorner);
    }

    return worldBounds;
}
