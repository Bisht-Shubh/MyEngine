#include "pch.h"
#include "PointLight.h"

#include <iostream>
#include <string>

PointLight::PointLight(EntityID entityID)
    : Light(entityID)
{
	std::cout << "\n--------------------------------------------\n";
	std::cout << "\nDEBUG::PointLight succesfully created with properties:\n";
	std::cout << "Ambient: (" << ambient.x << ", " << ambient.y << ", " << ambient.z << ")\n";
	std::cout << "Diffuse: (" << diffuse.x << ", " << diffuse.y << ", " << diffuse.z << ")\n";
	std::cout << "Specular: (" << specular.x << ", " << specular.y << ", " << specular.z << ")\n";
	std::cout << "Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
	std::cout << "Intensity: " << intensity << "\n";
	std::cout << "--------------------------------------------\n";
}

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

void PointLight::ApplyLight(Shader& shader, int index) const
{
    const std::string prefix =
        "pointLights[" + std::to_string(index) + "].";

    shader.SetVector3f(prefix + "position", pos);
    shader.SetVector3f(prefix + "ambient", ambient);
    shader.SetVector3f(prefix + "diffuse", diffuse);
    shader.SetVector3f(prefix + "specular", specular);

    shader.SetFloat(prefix + "intensity", intensity);
    shader.SetFloat(prefix + "constant", 1.0f);
    shader.SetFloat(prefix + "linear", 0.09f);
    shader.SetFloat(prefix + "quadratic", 0.032f);
}
