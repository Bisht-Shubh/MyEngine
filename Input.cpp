#include "pch.h"

#include "GLFW/glfw3.h"
#include "Input.h"

void Input::OnKeyPressed(int key, int action)
{
	if (key < 0 || key >= 1024)
		return;

	if (action == GLFW_PRESS)
		m_keys[key] = true;
	else if (action == GLFW_RELEASE)
		m_keys[key] = false;
}

bool Input::IsKeyPressed(int key)
{
	return (key >= 0 && key < 1024) ? m_keys[key] : false;
}

void Input::OnMouseMove(double xpos, double ypos)
{
	if (m_firstMouse)
	{
		m_lastX = xpos;
		m_lastY = ypos;
		m_firstMouse = false;
	}

	m_MouseXOffset = static_cast<float>(xpos - m_lastX);
	m_MouseYOffset = static_cast<float>(m_lastY - ypos);

	m_lastX = xpos;
	m_lastY = ypos;
}

float Input::GetMouseXOffset() const
{
	return m_MouseXOffset;
}

float Input::GetMouseYOffset() const
{
	return m_MouseYOffset;
}

float Input::GetMouseX() const
{
	return static_cast<float>(m_lastX);
}

float Input::GetMouseY() const
{
	return static_cast<float>(m_lastY);
}

void Input::ResetMouseDelta()
{
	m_MouseXOffset = 0.0f;
	m_MouseYOffset = 0.0f;
}
