#pragma once
#include "EntityID.h"
#include<string>

class Scene;

class Entity
{
public:
	Entity() = default;
	Entity(EntityID id, Scene* scene);

	void SetName(const std::string& name);

	// Lookups
	const std::string& GetName() const;
	EntityID GetID() const;

private:
	EntityID m_id;
	std::string m_name;

	Scene* m_scene;
};

