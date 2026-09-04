#pragma once
#include "Light.h"

class SpotLight :
    public Light
{
public:
	SpotLight(EntityID entityID);

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
	float innerAngle{ 35.5f };			// degrees
	float outerAngle{ 50.5f };			// degrees
	glm::vec3 position{0.0f, 12.0f, 0.0f};
	glm::vec3 direction{0.0f, -1.0f, 0.0f};
	float constant{ 1.0f };
	float linear{ 0.09f };
	float quadratic{ 0.032f };
	float intensity{ 2.0f };
};

