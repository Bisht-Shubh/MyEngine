#include "pch.h"
#include "PointLight.h"

PointLight::PointLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 pos, float intensity)
    : Light(amb, diff, spec), pos(pos), intensity(intensity)
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

void PointLight::ApplyLight(Shader& shader) const
{
	shader.SetVector3f("pointLight.position", pos);
	shader.SetVector3f("pointLight.ambient", ambient);
	shader.SetVector3f("pointLight.diffuse", diffuse);
	shader.SetVector3f("pointLight.specular", specular);
	shader.SetFloat("pointLight.intensity", intensity);
	shader.SetFloat("pointLight.constant", 1.0f);
	shader.SetFloat("pointLight.linear", 0.09f);
	shader.SetFloat("pointLight.quadratic", 0.032f);
}
