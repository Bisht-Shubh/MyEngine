#pragma once

#include "Input.h"
#include "Window.h"
#include "imGuiLayer.h"
#include "Engine.h"

class Application
{
public:

    Application();
    ~Application();

    void Init();
    void Run();

private:

    Input m_input;

    Window m_window;

    imGuiLayer m_imguiLayer;

    Engine m_engine;

    float m_deltaTime{ 0.0f };
    float m_lastFrame{ 0.0f };
};