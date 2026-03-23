#pragma once
#include "MeshRenderer.h"
class Cube :
	public MeshRenderer
{
public:

	Cube();
	Cube(Shader& shader, unsigned int width, unsigned int height);

	virtual void DrawMesh() override;

	virtual void SetViewProjection(const glm::mat4& view, const glm::mat4& projection);

private:
	virtual void InitRenderData() override;

};

