#include "pch.h"
#include "EntityManager.h"

#include<iostream>
#include<algorithm>


EntityManager::EntityManager(Scene* scene)
	: m_scene(scene)
{}

Entity EntityManager::CreateEntity(const std::string& name)
{
	EntityID id = m_nextID++;

	m_entities.emplace_back(EntityData{id, name});

	std::cout << "\nDEBUG::MESSAGE::Created Entity with name :: " << name << " :: and ID :: " << id;

	Entity entity(id, m_scene);

	entity.SetName(name);

	std::cout << "\nDEBUG::CREATE_ENTITY()::Entity count :: " << m_entities.size();
	std::cout << "\nCREATE MANAGER ADDRESS: " << this;

	return entity;
}

void EntityManager::DestroyEntity(EntityID id)
{
	std::cout << "\nDESTROY MANAGER ADDRESS: " << this;
	std::cout << "\nDESTROY ENTITY COUNT: " << m_entities.size();

	auto it = std::find_if(m_entities.begin(), m_entities.end(), [id](const EntityData& entity)
		{
			return entity.id == id;
		});

	if (it != m_entities.end())
	{
		std::cout << "\nDEBUG::DELETING::ENTITY_WITH_ID::" << id;
		m_entities.erase(it);
	}
	else
	{
		std::cout
			<< "\nDEBUG::WARNING::ENTITY_MANAGER::DESTROY_ENTITY::"
			<< "Entity with ID :: " << id << " :: is invalid";
	}
}

Entity EntityManager::GetEntity(EntityID id)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [id](const EntityData& entity)
		{
			return entity.id == id;
		});

	if (it == m_entities.end())
	{
		std::cout << "\nDEBUG::WARNING::ENTITY_MANAGER::GET_ENTITY::Invalid Entity ID :: ID ::" << id;
		return Entity{};
	}

	Entity entity(id, m_scene);
	entity.SetName(it->name);

	return entity;
}

Entity EntityManager::FindEntity(const std::string& name)
{
	auto it = std::find_if(m_entities.begin(), m_entities.end(), [&name](const EntityData& entity)
		{
			return entity.name == name;
		});

	if (it == m_entities.end())
	{
		std::cout << "\nDEBUG::WARNING::ENTITY_MANAGER::FIND_ENTITY::Entity not found :: ENTITY_NAME :: " << name;
		return Entity{};
	}

	
	return GetEntity(it->id);
}

bool EntityManager::Exists(EntityID id) const
{
	// Use a predicate to compare EntityData.id with the requested id
	return std::find_if(m_entities.begin(), m_entities.end(), [id](const EntityData& entity)
		{
			return entity.id == id;
		}) != m_entities.end();
}

const std::vector<EntityData>& EntityManager::GetAllEntities() const
{
	return m_entities;
}


