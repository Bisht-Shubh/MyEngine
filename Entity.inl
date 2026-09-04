#include "Entity.h"

template <typename T>
T* Entity::AddComponent()
{
	if (!m_scene)
	{
		std::cout << "DEBUG::WARNING::ENTITY::ADD_COMPONENT::"
			<< "Entity is not associated with a Scene. Cannot add component." << std::endl;
		return nullptr;
	}
	return m_scene->GetComponentManager().template CreateComponent<T>(GetID());

}

template <typename T>
T* Entity::GetComponent()
{
	if (!m_scene)
	{
		std::cout << "DEBUG::WARNING::ENTITY::GET_COMPONENT::"
			<< "Entity is not associated with a Scene. Cannot get component." << std::endl;
		return nullptr;
	}
	return m_scene->GetComponentManager().template GetComponent<T>(GetID());
}
