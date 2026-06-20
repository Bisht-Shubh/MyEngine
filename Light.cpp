#include "pch.h"
#include "Light.h"

Light::Light(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
	: ambient(amb), diffuse(diff), specular(spec) {}

glm::vec3 Light::GetAmbient(const glm::vec3& amb)
{
	return ambient;
}

glm::vec3 Light::GetDiffuse(const glm::vec3& diff)
{
	return diffuse;
}

glm::vec3 Light::GetSpecular(const glm::vec3& spec)
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

