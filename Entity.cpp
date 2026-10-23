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

void Entity::Clone(EntityID sourceID, EntityID newID)
{
	// copy components of Entity with Id 1 to entity with Id 2
	Entity sourceEntity = m_scene->GetEntityManager().GetEntity(sourceID);
	Entity newEntity = m_scene->GetEntityManager().GetEntity(newID);

    // MeshRenderer
    if (MeshRenderer* sourceMesh = sourceEntity.GetComponent<MeshRenderer>())
    {
        MeshRenderer* newMesh = newEntity.AddComponent<MeshRenderer>();

        if (!newMesh)
            return;

        newMesh->SetModel(sourceMesh->GetModel());
        newMesh->SetMaterial(sourceMesh->GetMaterial());
    }

    // Transform
    if (Transform* sourceTransform = sourceEntity.GetComponent<Transform>())
    {
        Transform* newTransform = newEntity.AddComponent<Transform>();

        if (!newTransform)
            return;

        newTransform->SetPosition(sourceTransform->GetPosition());
        newTransform->SetRotation(sourceTransform->GetRotation());
        newTransform->SetScale(sourceTransform->GetScale());
    }

     //SpotLight
    //if (SpotLight* sourceSpotlight = sourceEntity.GetComponent<SpotLight>())
    //{
    //    SpotLight* newSpotLight = newEntity.AddComponent<SpotLight>();

    //    if (!newSpotLight)
    //        return;

    //    newSpotLight->SetPosition(sourceSpotlight->GetPosition());
    //}
}
