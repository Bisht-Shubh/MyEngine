#pragma once
#include "Light.h"

class SpotLight :
    public Light
{
public:
	SpotLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 pos, glm::vec3 dir, float innerAngle, float outerAngle);

	float GetInnerAngle() const;
	float GetOuterAngle() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetDirection() const;

	void SetInnerAngle(float innerAngle);
	void SetOuterAngle(float outerAngle);
	void SetIntensity(float intensity);

	virtual void SetPosition(const glm::vec3& pos);
	virtual void SetDirection(const glm::vec3& dir);
	virtual void ApplyLight(Shader& shader) const override;

private:
	float innerAngle;			// degrees
	float outerAngle;			// degrees
	glm::vec3 position;
	glm::vec3 direction;
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;
	float intensity = 1.0f;
};

