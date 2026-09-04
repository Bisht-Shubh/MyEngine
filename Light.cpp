#include "pch.h"
#include "Light.h"

Light::Light(EntityID entityID)
	: Component(entityID) {}

glm::vec3 Light::GetAmbient() const
{
	return ambient;
}

glm::vec3 Light::GetDiffuse() const
{
	return diffuse;
}

glm::vec3 Light::GetSpecular() const
{
	return specular;
}

void Light::SetAmbient(const glm::vec3& amb)
{
	ambient = amb;
}

void Light::SetDiffuse(const glm::vec3& diff)
{
	diffuse = diff;
}

void Light::SetSpecular(const glm::vec3& spec)
{
	specular = spec;
}

void Light::SetPosition(const glm::vec3& pos)
{
	// Base Light class does not have a position, throw exception
	throw std::logic_error("Base Light class does not have a position. Use derived classes for specific light types.");

}

void Light::SetDirection(const glm::vec3& dir)
{
	// Base Light class does not have a direction, throw exception
	throw std::logic_error("Base Light class does not have a direction. Use derived classes for specific light types.");
}

