#pragma once

#include "Input.h"
#include "Game.h"
#include "EditorLayer.h"
#include "DebugLayer.h"
#include "Renderer.h"

class ImGuiLayer;

class Engine
{
public:

    Engine(
        Input& input,
        imGuiLayer& imguiLayer
    );

    ~Engine();

    void Init();
    void Update(float deltaTime);
    void Render();

    DebugLayer& GetDebugLayer();
    EditorLayer& GetEditorLayer()
    {
        return m_editorLayer;
    }

private:

    void LoadResources();

private:

    Input& m_input;

    DebugLayer m_debugLayer;

    Game m_game;

    EditorLayer m_editorLayer;
	imGuiLayer& m_imguiLayer;

    Renderer m_renderer;
};