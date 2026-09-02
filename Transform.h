#pragma once
#include<iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

	void SetPosition(const glm::vec3& position);
	void Translate(float x, float y, float z);

	void SetRotation(const glm::vec3& rotation);
	void Rotate(float x, float y, float z);

	void SetScale(const glm::vec3& scale);
	void Scale(float x, float y, float z);

	const glm::vec3& GetPosition() const;
	const glm::vec3& GetRotation() const;
	const glm::vec3& GetScale() const;

	glm::vec3 Forward() const;
	glm::vec3 Right() const;
	glm::vec3 Up() const;
	
	void Reset();

	glm::mat4 GetModelMatrix() const;

private:
	void RecalculateModelMatrix() const;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	mutable glm::mat4 m_ModelMatrix{ 1.0f };
	mutable bool m_Dirty{ true };
};

