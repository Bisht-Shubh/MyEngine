#pragma once
#include "Component.h"

#include <vector>
#include <string>
#include <memory>				
#include <iostream>

class Scene; // forward declaration to avoid circular include

class ComponentManager
{
public:
	ComponentManager() = default;
	ComponentManager(Scene* scene);

	//Component lifecycles
	template<typename T>
	T* CreateComponent(EntityID entityID)
	{
		auto component = std::make_unique<T>(entityID);

		std::cout << "\nDEBUG::MESSAGE::Created Component";

		T* ptr = component.get();

		m_components.push_back(std::move(component));

		std::cout << "\nDEBUG::CREATE_COMPONENT()::Component count :: " << m_components.size();

		return ptr;
	}

	template<typename T>
	T* GetComponent(EntityID entityID)
	{
		for (auto& comp : m_components) {
			if (comp->GetEntityID() == entityID) {
				if (T* ptr = dynamic_cast<T*>(comp.get())) return ptr;
			}
		}
		return nullptr;
	}

	void DestroyComponent(Component* component);


private:
	Scene* m_scene = nullptr;
	std::vector<std::unique_ptr<Component>> m_components;
};


