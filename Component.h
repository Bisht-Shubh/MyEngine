#pragma once
#include "EntityID.h"

class Component
{
public:
	Component(EntityID entityID)
		: m_entityID(entityID) {}

	EntityID GetEntityID() const { return m_entityID; }

	virtual ~Component() = default;

private:
	EntityID m_entityID;
};

	