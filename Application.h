#pragma once

#include "Window.h"
#include "Input.h"
#include "Engine.h"
#include "imGuiLayer.h"

class Application
{
private:
    Input m_input;
    Window m_window;
    Engine m_engine;
    imGuiLayer m_imguiLayer;

    float m_deltaTime = 0.0f;
    float m_lastFrame = 0.0f;

public:
    Application();
    ~Application();

    // Prevent copying
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void Init();
    void Run();
};