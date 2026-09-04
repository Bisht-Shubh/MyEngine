#include "pch.h"
#include "SpotLight.h"

SpotLight::SpotLight(EntityID entityID)
	: Light(entityID)
{
	innerAngle = glm::cos(glm::radians(innerAngle));
	outerAngle = glm::cos(glm::radians(outerAngle));
}
	
float SpotLight::GetInnerAngle() const
{
	return innerAngle;
}

float SpotLight::GetOuterAngle() const
{
	return outerAngle;
}

glm::vec3 SpotLight::GetPosition() const
{
	return position;
}

glm::vec3 SpotLight::GetDirection() const
{
	return direction;
}

void SpotLight::SetInnerAngle(float innerAngle)
{
	this->innerAngle = innerAngle;
	this->innerAngle = glm::cos(glm::radians(innerAngle));
}

void SpotLight::SetOuterAngle(float outerAngle)
{
	this->outerAngle = outerAngle;
	this->outerAngle = glm::cos(glm::radians(outerAngle));
}

void SpotLight::SetIntensity(float intensity)
{
	this->intensity = intensity;
}

void SpotLight::SetPosition(const glm::vec3& pos)
{
	this->position = pos;
}

void SpotLight::SetDirection(const glm::vec3& dir)
{
	this->direction = dir;
}

void SpotLight::ApplyLight(Shader& shader) const
{
	shader.SetVector3f("spotLight.position", position);
	shader.SetVector3f("spotLight.direction", direction);
	shader.SetFloat("spotLight.innerAngle", innerAngle);
	shader.SetFloat("spotLight.outerAngle", outerAngle);
	shader.SetVector3f("spotLight.ambient", ambient);
	shader.SetVector3f("spotLight.diffuse", diffuse);
	shader.SetVector3f("spotLight.specular", specular);
	shader.SetFloat("spotLight.constant", constant);
	shader.SetFloat("spotLight.linear", linear);
	shader.SetFloat("spotLight.quadratic", quadratic);
	shader.SetFloat("spotLight.intensity", intensity);
}
