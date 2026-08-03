#pragma once
#include "Light.h"
class PointLight :
    public Light
{
public:
	PointLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 pos, float intensity);
	
	glm::vec3 pos;
	float intensity;

	glm::vec3 GetPosition() const;
	
	virtual void SetPosition(const glm::vec3& pos);
	void SetIntensity(float intensity);
};

