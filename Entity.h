#pragma once
#include "EntityID.h"
#include<string>
#include <iostream>

#include "Component.h"

class Scene;

class Entity
{
	private:
	EntityID m_id;
	std::string m_name;

	Scene* m_scene;
public:
	Entity() = default;
	Entity(EntityID id, Scene* scene);

	void SetName(const std::string& name);

	// Lookups
	const std::string& GetName() const;
	EntityID GetID() const;

	// Component management
	// Add a component of type T to the entity
	template<typename T>
	T* AddComponent();

	template<typename T>
	T* GetComponent();

	void RemoveComponent(Component* component);
	void Clone(EntityID sourceID, EntityID newId);
};

