#include "pch.h"
#include "DirectionalLight.h"
#include "ResourceManager.h"

DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
	: Light(amb, diff, spec), direction(dir)
{
	
}

glm::vec3 DirectionalLight::GetDirection()
{
	return direction;
}

void DirectionalLight::ApplyLight(Shader& shader) const
{
	shader.SetVector3f("lightDir", direction);
	shader.SetVector3f("lightAmbient", ambient);
	shader.SetVector3f("lightDiffuse", diffuse);
	shader.SetVector3f("lightSpecular", specular);
}


