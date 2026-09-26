#include "pch.h"
#include "imGuiLayer.h"
#include<iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

void imGuiLayer::Init(GLFWwindow* window)
{
	if (m_isInitialized)
	{
		std::cout << "DEBUG::ERROR::imGuiLayer is already initialized." << std::endl;
		return;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); 

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
	m_isInitialized = true;
}

void imGuiLayer::BeginFrame()
{
	if (!m_isInitialized)
	{
		std::cout << "DEBUG::WARNING::IMGUI_LAYER::BEGIN()::imGuiLayer is not initialized." << std::endl;
		return;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
}

void imGuiLayer::EndFrame()
{
	if (!m_isInitialized)
	{
		std::cout << "DEBUG::WARNING::IMGUI_LAYER::END()::imGuiLayer is not initialized." << std::endl;
		return;
	}

	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imGuiLayer::Shutdown()
{
	if (!m_isInitialized)
		return;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	m_isInitialized = false;
}
