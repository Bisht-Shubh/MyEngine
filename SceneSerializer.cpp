#include "pch.h"
#include "SceneSerializer.h"

#include <fstream>

bool SceneSerializer::Save(const json& data, const std::string& filePath)
{
	std::ofstream file(filePath);

	if(!file.is_open())
		return false;

	file << data.dump(4); 

	return true;
}

bool SceneSerializer::Load(json& data, const std::string& filePath)
{
	std::ifstream file(filePath);

	if(!file.is_open())
		return false;

	file >> data;

	return true;
}
