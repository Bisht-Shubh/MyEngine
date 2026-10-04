#pragma once

#include <json.hpp>

class Scene;

using json = nlohmann::json;

class SceneSerializer
{
public:
	static bool Serialize(Scene& scene, const std::string& filePath);
	static bool Deserialize(Scene& scene, const std::string& filePath);

private:
	static bool Load(json& data, const std::string& filePath);
	static bool Save(const json& data, const std::string& filePath);
};

