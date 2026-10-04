#pragma once

#include <json.hpp>
#include "Transform.h"

using json = nlohmann::json;

class SceneSerializer
{
public:
	static bool Save(const json& data, const std::string& filePath);
	static bool Load(json& data, const std::string& filePath);
};

