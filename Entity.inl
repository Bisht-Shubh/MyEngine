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
	return m_scene->GetComponentManager().template CreateComponent<T>();

}
