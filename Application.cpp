#include "pch.h"
#include "Application.h"

#include <imgui.h>

Application::Application()
    : m_input(),
    m_window(1400, 1200, m_input),
    m_engine(m_input)
{
}

Application::~Application()
{
    m_imguiLayer.Shutdown();
}

void Application::Init()
{
    m_window.InitWindow();

    m_engine.Init();

    m_imguiLayer.Init(m_window.GetWindow());
}

void Application::Run()
{
    while (!m_window.ShouldClose())
    {
        glfwPollEvents();

        // Calculate delta time
        float currentFrame = static_cast<float>(glfwGetTime());

        m_deltaTime = currentFrame - m_lastFrame;

        m_lastFrame = currentFrame;

        m_window.Update();

        m_engine.Update(m_deltaTime);

        // Engine rendering
        m_engine.Render();

        // -------------------------------
        // ImGui
        // -------------------------------

        m_imguiLayer.BeginFrame();

        ImGui::SetNextWindowSize(ImVec2(250, 170));

        ImGui::SetNextWindowPos(ImVec2(1200, 10));

        ImGui::Begin("Debug Window");

        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

        ImGui::Text("RAM Usage: %.2f MB" ,m_engine.GetDebugLayer().GetMemoryUsage()/ (1024.0 * 1024.0));

        ImGui::Text("Shader Load Time: %d ms", m_engine.GetDebugLayer().GetShaderLoadTime());

        ImGui::Text("Shader Count: %zu", ResourceManager::Shaders.size());

        ImGui::End();

        m_imguiLayer.EndFrame();

        // Present frame
        glfwSwapBuffers(m_window.GetWindow());
    }
}