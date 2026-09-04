#include "pch.h"
#include "DirectionalLight.h"
#include "ResourceManager.h"

DirectionalLight::DirectionalLight(EntityID entityID)
	: Light(entityID)
{
	
}

glm::vec3 DirectionalLight::GetDirection()
{
	return direction;
}

void DirectionalLight::SetDirection(float x, float y, float z)
{
	direction = glm::vec3(x, y, z);
}

void DirectionalLight::ApplyLight(Shader& shader) const
{
	shader.SetVector3f("lightDir", direction);
	shader.SetVector3f("lightAmbient", ambient);
	shader.SetVector3f("lightDiffuse", diffuse);
	shader.SetVector3f("lightSpecular", specular);
}


