#pragma once

#include <glm/glm.hpp>
#include <limits>

struct BoundingBox {
	glm::vec3 min;
	glm::vec3 max;
};

inline BoundingBox TransformBoundingBox(
    const BoundingBox& localBounds,
    const glm::mat4& modelMatrix)
{
    BoundingBox worldBounds{
        glm::vec3(std::numeric_limits<float>::max()),
        glm::vec3(std::numeric_limits<float>::lowest())
    };

    for (int i = 0; i < 8; ++i)
    {
        glm::vec3 corner(
            (i & 1) ? localBounds.max.x : localBounds.min.x,
            (i & 2) ? localBounds.max.y : localBounds.min.y,
            (i & 4) ? localBounds.max.z : localBounds.min.z
        );

        glm::vec3 worldCorner = glm::vec3(
            modelMatrix * glm::vec4(corner, 1.0f));

        worldBounds.min = glm::min(worldBounds.min, worldCorner);
        worldBounds.max = glm::max(worldBounds.max, worldCorner);
    }

    return worldBounds;
}
