#include "pch.h"
#include "Entity.h"

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
