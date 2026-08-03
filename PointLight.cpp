#include "pch.h"
#include "PointLight.h"

PointLight::PointLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 pos, float intensity)
    : Light(amb, diff, spec), pos(pos), intensity(intensity)
{}

glm::vec3 PointLight::GetPosition() const
{
    return pos;
}

void PointLight::SetPosition(const glm::vec3& pos)
{
    this->pos = pos;
}

void PointLight::SetIntensity(float intensity)
{
    this->intensity = intensity;
}
