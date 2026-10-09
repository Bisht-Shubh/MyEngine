#include "pch.h"
#include "SpotLight.h"

SpotLight::SpotLight(EntityID entityID)
	: Light(entityID)
{
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

float SpotLight::GetIntensity() const
{
	return intensity;
}

void SpotLight::SetInnerAngle(float innerAngle)
{
	this->innerAngle = innerAngle;
}

void SpotLight::SetOuterAngle(float outerAngle)
{
	this->outerAngle = outerAngle;
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

void SpotLight::ApplyLight(Shader& shader, int index) const
{
	const std::string prefix = "spotLights[" + std::to_string(index) + "].";

	shader.SetVector3f(prefix + "position", position);
	shader.SetVector3f(prefix + "direction", direction);
	shader.SetFloat(prefix + "innerAngle", innerAngle);
	shader.SetFloat(prefix + "outerAngle", outerAngle);
	shader.SetVector3f(prefix + "ambient", ambient);
	shader.SetVector3f(prefix + "diffuse", diffuse);
	shader.SetVector3f(prefix + "specular", specular);
	shader.SetFloat(prefix + "constant", constant);
	shader.SetFloat(prefix + "linear", linear);
	shader.SetFloat(prefix + "quadratic", quadratic);
	shader.SetFloat(prefix + "intensity", intensity);
}
