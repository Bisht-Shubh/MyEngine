#pragma once

//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------DIRECTIONAL LIGHT CLASS---------------------------------------------------------//
//-----------------------------------------EXTENDS THE LIGHT CLASS---------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

// The DirectionalLight class represents a light source that has a specific direction but no position, like sunlight.

#include "Light.h"
class DirectionalLight : public Light
{
private:
	// General directional light properties
	

public:
	glm::vec3 direction;
	// Constructor to initialize directional light properties
	DirectionalLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec);

	// Get direction of the light
	glm::vec3 GetDirection();

	// Apply directional light properties to the shader
	void ApplyLight(Shader& shader) const override;
};

