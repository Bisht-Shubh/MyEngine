#include "pch.h"
#include "Application.h"

Application::Application()
    : m_input(),
    m_window(
        2260,
        1440,
        m_input
    ),
    m_imguiLayer(),
    m_engine(
        m_input,
        m_imguiLayer
    )
{
}

Application::~Application()
{
    m_imguiLayer.Shutdown();
}

void Application::Init()
{
    m_window.InitWindow();

    m_imguiLayer.Init(
        m_window.GetWindow()
    );

    m_engine.Init();
}

void Application::Run()
{
    while (!m_window.ShouldClose())
    {
        // --------------------------------
        // Delta time
        // --------------------------------

        float currentFrame =
            static_cast<float>(glfwGetTime());

        m_deltaTime =
            currentFrame - m_lastFrame;

        m_lastFrame = currentFrame;


        // --------------------------------
        // Input / Window
        // --------------------------------

        m_window.Update();


        // --------------------------------
        // Engine
        // --------------------------------

        m_engine.Update(m_deltaTime);

        m_engine.Render();


        // --------------------------------
        // Present
        // --------------------------------

        glfwSwapBuffers(
            m_window.GetWindow()
        );
    }
}