#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Input.h"

//-----------------------------------------------------------------------------------------//
//------Window class is responsible for creating and managing the window using GLFW.-------// 
//---------It handles window creation and provides access to the GLFWwindow object.--------//
// ----------------------------------------------------------------------------------------//

class Window
{
public:
	// Input
	bool Keys[1024];
	bool KeysProcessed[1024];

	Window(unsigned int width, unsigned int height, Input& input);
	~Window();

	void InitWindow();

	GLFWwindow* GetWindow() const;

	bool ShouldClose() const;

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;

	void Update();

private:
	GLFWwindow* m_window;
	

	// frame timings
	float m_deltaTime{ 0.0f };
	float m_lastFrame{ 0.0f };

	unsigned int m_Width, m_Height;

	// Input
	Input& m_input;

	//-----------------------------------------------------------------------------------------//
	//------Static callback functions for GLFW input handling. These functions are called by----//
	//------GLFW when specific events occur, such as window resizing or key presses.------------//
	//-----------------------------------------------------------------------------------------//

	static void framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height);
	static void key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mode);

	static void mouseCallBack(GLFWwindow* glfwWindow, double xPos, double yPos);
};

