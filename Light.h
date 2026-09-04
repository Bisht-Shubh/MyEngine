#pragma once

//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------GENERAL LIGHT CLASS---------------------------------------------------------//
//---------------------------------EXTENDED BY DIRECTIONAL, POINT AND SPOT LIGHTS------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

// Class and child classes will contain properties and methods for light sources in the scene, such as position, color, intensity, and direction. 
// These classes will be used to calculate lighting effects in the shaders 
// and will be passed to the shaders as uniform variables to affect the rendering of objects in the scene.
// The Light class will serve as a base class for different types of lights, such as directional lights, point lights, and spotlights.

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Component.h"

class Light : public Component
{
protected:
	// General light properties
	glm::vec3 ambient{ 1.5f, 1.5f, 1.5f };
	glm::vec3 diffuse{ 0.6f, 0.6f, 0.6f };
	glm::vec3 specular{ 1.6f, 1.6f, 1.6f };

public:

	// Constructor to initialize light properties
	Light(EntityID entityID);
	virtual ~Light() = default;  // Virtual destructor for proper cleanup of derived classes

	// getters 
	glm::vec3 GetAmbient() const;
	glm::vec3 GetDiffuse() const;
	glm::vec3 GetSpecular() const;

	// setters
	void SetAmbient(const glm::vec3& amb);
	void SetDiffuse(const glm::vec3& diff);
	void SetSpecular(const glm::vec3& spec);
	virtual void SetPosition(const glm::vec3& pos);
	virtual void SetDirection(const glm::vec3& dir);
	virtual void ApplyLight(Shader& shader) const = 0;   // Pure virtual function to apply light properties to the shader
};

