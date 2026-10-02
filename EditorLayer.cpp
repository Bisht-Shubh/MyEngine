#include "pch.h"
#include "EditorLayer.h"

#include "Game.h"
#include "Scene.h"
#include "Input.h"
#include "DebugLayer.h"
#include "imGuiLayer.h"
#include "ResourceManager.h"

#include <GLFW/glfw3.h>
#include <imgui.h>

EditorLayer::EditorLayer(
    Game& game,
    Input& input,
    DebugLayer& debugLayer,
    imGuiLayer& imguiLayer
)
    : m_game(game),
    m_input(input),
    m_debugLayer(debugLayer),
    m_imguiLayer(imguiLayer)
{
}

void EditorLayer::Update(float deltaTime)
{
    Scene* scene = m_game.GetCurrentScene();

    if (!scene)
        return;

	scene->Update(deltaTime);
    // --------------------------------
    // Editor logic
    // --------------------------------

    // Editor camera
    // Entity selection
    // Transform manipulation
    // etc.


    // --------------------------------
    // ImGui
    // --------------------------------

    m_imguiLayer.BeginFrame();

    ImGui::SetNextWindowSize(ImVec2(250, 170));
    ImGui::SetNextWindowPos(ImVec2(1200, 10));

    ImGui::Begin("Debug Window");

    ImGui::Text(
        "FPS: %.1f",
        ImGui::GetIO().Framerate
    );

    ImGui::Text(
        "RAM Usage: %.2f MB",
        m_debugLayer.GetMemoryUsage() /
        (1024.0 * 1024.0)
    );

    ImGui::Text(
        "Shader Load Time: %d ms",
        m_debugLayer.GetShaderLoadTime()
    );

    ImGui::Text(
        "Shader Count: %zu",
        ResourceManager::Shaders.size()
    );

    ImGui::End();
}

void EditorLayer::CheckInput()
{
    if (m_input.IsKeyPressed(GLFW_KEY_F1))
    {
        if (!IsEditorMode())
            SwitchToEditorMode();
        
    }

    if (m_input.IsKeyPressed(GLFW_KEY_F2))
    {
        if (!IsGameMode())
            SwitchToGameMode();
    }
}

void EditorLayer::SwitchToEditorMode()
{
	std::cout << "\nDEBUG::MESSAGEL::Switching to Editor Mode\n";

	Scene* scene = m_game.GetCurrentScene();
    scene->GetCamera().DisableCam();

    m_mode = Mode::Editor;
}

void EditorLayer::SwitchToGameMode()
{
	std::cout << "\nDEBUG::MESSAGEL::Switching to Game Mode\n";
	Scene* scene = m_game.GetCurrentScene();
	scene->GetCamera().EnableCam();
    m_mode = Mode::Game;
}

bool EditorLayer::IsEditorMode() const
{
    return m_mode == Mode::Editor;
}

bool EditorLayer::IsGameMode() const
{
    return m_mode == Mode::Game;
}