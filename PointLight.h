#pragma once
#include "Light.h"
class PointLight :
    public Light
{
public:
	PointLight(EntityID entityID);
	
	glm::vec3 pos{0.0f, 0.0f, 0.0f};
	float intensity{1.0f};

	glm::vec3 GetPosition() const;
	
	virtual void SetPosition(const glm::vec3& pos);
	void SetIntensity(float intensity);
	
	virtual void ApplyLight(Shader& shader, int index) const override;
};

