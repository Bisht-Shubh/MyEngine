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
	float m_intensity{ 0.3f };  
	

public:
	glm::vec3 direction{ 0.0f, -1.0f, 0.0f };
	// Constructor to initialize directional light properties
	DirectionalLight(EntityID entityID);

	glm::vec3 GetDirection();
	void SetDirection(float x, float y, float z);

	// Apply directional light properties to the shader
	void ApplyLight(Shader& shader, int index) const override;
};

