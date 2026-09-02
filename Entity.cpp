#include "pch.h"
#include "Entity.h"
#include "Scene.h"

Entity::Entity(EntityID id, Scene* scene)
	: m_id(id), m_scene(scene)
{}

void Entity::SetName(const std::string& name)
{
	m_name = name;
}

const std::string& Entity::GetName() const
{
	return m_name;
}

EntityID Entity::GetID() const
{
	return m_id;
}

void Entity::RemoveComponent(Component* component)
{
	if (!m_scene)
	{
		std::cout << "DEBUG::WARNING::ENTITY::REMOVE_COMPONENT::"
			<< "Entity is not associated with a Scene. Cannot remove component." << std::endl;
		return;
	}
	m_scene->GetComponentManager().DestroyComponent(component);
}
