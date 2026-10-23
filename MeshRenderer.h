#pragma once

#include "Component.h"
#include "Model.h"
#include "Material.h"
#include <json.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

using json = nlohmann::json;

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

    // Serialization
    json Serialze() const;
    void Deserialize(const json& data);

private:
    Model* m_model = nullptr    ;
	Material* m_material = nullptr;
};