#include "pch.h"
#include "Material.h"

Material::Material(Shader* shader)
	: m_shader(shader)
{
}

void Material::SetShader(Shader* shader)
{
	m_shader = shader;
}

Shader* Material::GetShader() const
{
	return m_shader;
}
