#pragma once
#include "Shader.h"

class Material
{
public:
	Material(Shader* shader);

	void SetShader(Shader* shader);
	Shader* GetShader() const;

private:
	Shader* m_shader;
};

