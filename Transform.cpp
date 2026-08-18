#include "pch.h"
#include "Transform.h"

Transform::Transform()
{}

Transform::Transform(const glm::vec3 & position, const glm::vec3 & rotation, const glm::vec3 & scale)
{}

void Transform::SetPosition(const glm::vec3 & position)
{
	if (m_Position == position)
		return;						// do not update if the position is the same

	m_Position = position;
	m_Dirty = true;
}


void Transform::Translate(float x, float y, float z)
{
	m_Position += glm::vec3(x, y, z);
	m_Dirty = true;
}

void Transform::SetRotation(const glm::vec3& rotation)
{
	if (m_Rotation == rotation)
		return;						// do not update if the rotation is the same

	m_Rotation = rotation;
	m_Dirty = true;
}

void Transform::Rotate(float x, float y, float z)
{
	m_Rotation += glm::vec3(x, y, z);
	m_Dirty = true;
}

void Transform::SetScale(const glm::vec3& scale)
{
	if (m_Scale == scale)
		return;						// do not update if the scale is the same

	m_Scale = scale;
	m_Dirty = true;
}

void Transform::Scale(float x, float y, float z)
{
	m_Scale *= glm::vec3(x, y, z);
	m_Dirty = true;
}

const glm::vec3& Transform::GetPosition() const
{
	return m_Position;
}

const glm::vec3& Transform::GetRotation() const
{
	return m_Rotation;
}

const glm::vec3& Transform::GetScale() const
{
	return m_Scale;
}

void Transform::Reset()
{
	m_Position = glm::vec3(0.0f);
	m_Rotation = glm::vec3(0.0f);
	m_Scale = glm::vec3(1.0f);
	m_Dirty = true;
}

glm::mat4 Transform::GetModelMatrix() const
{
	if (m_Dirty)
	{
		RecalculateModelMatrix();
		m_Dirty = false;
	}

	return m_ModelMatrix;
}

void Transform::RecalculateModelMatrix() const
{
	m_ModelMatrix = glm::mat4(1.0f);
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
	m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
}
