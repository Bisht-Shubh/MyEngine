#include "pch.h"
#include "ComponentManager.h"


ComponentManager::ComponentManager(Scene* scene)
	: m_scene(scene)
{}

void ComponentManager::DestroyComponent(Component* component)
{
	if (!component)
	{
		std::cout << "\nDEBUG::WARNING::COMPONENT_MANAGER::DESTROY_COMPONENT::"
			<< "Attempted to destroy null component";
		return;
	}

	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		if (it->get() == component)
		{
			std::cout << "\nDEBUG::DELETING::COMPONENT";
			m_components.erase(it);
			return;
		}
	}

	std::cout << "\nDEBUG::WARNING::COMPONENT_MANAGER::DESTROY_COMPONENT::"
		<< "Component not found";
}

