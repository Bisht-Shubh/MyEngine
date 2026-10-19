#pragma once

#include<vector>
#include<string>

#include "EntityID.h"
#include "Entity.h"

class Scene;

struct EntityData {
	EntityID id;
	std::string name;
};

class EntityManager
{
public:
	EntityManager() = default;
	EntityManager(Scene* scene);

	//Entity lifecycles
	Entity CreateEntity(const std::string& name);
	void DestroyEntity(EntityID id);

	//Entity lookup
	Entity GetEntity(EntityID id);
	Entity FindEntity(const std::string& name);
	bool Exists(EntityID id) const;
	const std::vector<EntityData>& GetAllEntities() const;

	void DuplicateEntity(EntityID sourceID);
		
private:
	Scene* m_scene = nullptr;
	EntityID m_nextID = 1;
	std::vector<EntityData> m_entities;
};

