#pragma once

#include "Component.h"
#include "Model.h"
#include "Material.h"

class MeshRenderer : public Component
{
public:
    MeshRenderer(EntityID entityID)
        : Component(entityID)
    {
    }

    // Models
    void SetModel(Model* model);
    Model* GetModel() const;

    // Materials
    void SetMaterial(Material* material);
	Material* GetMaterial() const;

private:
    Model* m_model = nullptr    ;
	Material* m_material = nullptr;
};