#include "pch.h"
#include "SceneSerializer.h"

#include "Scene.h"
#include "Entity.h"
#include "Transform.h"

#include <string>

#include <fstream>

bool SceneSerializer::Serialize(Scene& scene, const std::string& filePath)
{
    json sceneData;


	const auto& entities = scene.GetEntityManager().GetAllEntities();

    for(const EntityData& entityData : entities)
    {
		// Process each entity and its components
		Entity entity = scene.GetEntityManager().GetEntity(entityData.id);

		json& entityJson = sceneData["entities"][std::to_string(entityData.id)];
		entityJson["name"] = entityData.name;

		// Serialize Transform component if it exists
		Transform* transform = entity.GetComponent<Transform>();

		if (transform)
			entityJson["transform"] = transform->Serialize();
    }

	return Save(sceneData, filePath);
}

bool SceneSerializer::Deserialize(Scene& scene, const std::string& filePath)
{
    json sceneData;

    if (!Load(sceneData, filePath))
        return false;

	if (!sceneData.contains("entities"))
		return false;

	const auto& entities = sceneData["entities"];

    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
		EntityID id = static_cast<EntityID>(std::stoul(it.key()));

		if (!scene.GetEntityManager().Exists(id))
		{
			std::cerr << "/nDEBUG::ERROR::Entity with ID " << id << " does not exist in the scene." << std::endl;
			continue;
		}

		Entity entity = scene.GetEntityManager().GetEntity(id);

		if (!it.value().contains("transform"))
			continue;

        // Enitity components
        // Transform
		Transform* transform = entity.GetComponent<Transform>();

        if(transform)
			transform->Deserialize(it.value()["transform"]);

        MeshRenderer* meshRenderer = entity.GetComponent<MeshRenderer>();

        //if(meshRenderer)
        //    meshRenderer->Deserializ
    }

	return true;

}

bool SceneSerializer::Save(const json& data, const std::string& filePath)
{
    std::ofstream file(filePath);

    if (!file.is_open())
        return false;

    file << data.dump(4);

    return true;
}

bool SceneSerializer::Load(json& data, const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
        return false;

    file >> data;

    return true;
}