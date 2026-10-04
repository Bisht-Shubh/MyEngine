#include "pch.h"
#include "SceneSerializer.h"

#include "Scene.h"
#include "Entity.h"
#include "Transform.h"

#include <fstream>

bool SceneSerializer::Serialize(Scene& scene, const std::string& filePath)
{
    json sceneData;

    Entity car = scene.GetEntityManager().FindEntity("Car");

    Transform* transform = car.GetComponent<Transform>();

    if (transform)
    {
        sceneData["entities"]["Car"]["transform"] =
            transform->Serialize();
    }

    return Save(sceneData, filePath);
}

bool SceneSerializer::Deserialize(Scene& scene, const std::string& filePath)
{
    json sceneData;

    if (!Load(sceneData, filePath))
        return false;

    Entity car = scene.GetEntityManager().FindEntity("Car");

    Transform* transform = car.GetComponent<Transform>();

    if (!transform)
        return false;

    const auto& transformData = sceneData.at("entities").at("Car").at("transform");

    transform->Deserialize(transformData);

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