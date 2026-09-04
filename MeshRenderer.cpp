#include "pch.h"
#include "MeshRenderer.h"


void MeshRenderer::SetModel(Model* model)
{
    m_model = model;
}

Model* MeshRenderer::GetModel() const
{
    return m_model;
}

void MeshRenderer::SetMaterial(Material* material)
{
    m_material = material;
}

Material* MeshRenderer::GetMaterial() const
{
    return m_material;
}
