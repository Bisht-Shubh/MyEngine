#include "pch.h"
#include "EditorLayer.h"

#include "Game.h"
#include "Scene.h"
#include "Input.h"
#include "DebugLayer.h"
#include "imGuiLayer.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Transform.h"

#include "SceneSerializer.h"

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

	// Transform Inspector
	Entity car = scene->GetEntityManager().FindEntity("Car");

	Transform* carTransform = car.GetComponent<Transform>();

	ImGui::Begin("Transform");

    if (carTransform)
    {
        // Position
        glm::vec3 position = carTransform->GetPosition();
        if (ImGui::DragFloat3("position", &position.x, 0.1f))
            carTransform->SetPosition(position);

        // Rotation
        glm::vec3 rotation = carTransform->GetRotation();
        if (ImGui::DragFloat3("rotation", &rotation.x, 0.5f))
            carTransform->SetRotation(rotation);

        // Scale
        glm::vec3 scale = carTransform->GetScale();
        if (ImGui::DragFloat3("scale", &scale.x, 0.1f))
            carTransform->SetScale(scale);
    }

    ImGui::End();

	ImGui::Begin("Scene");

    if(ImGui::Button("Save"))
    {
		if (SceneSerializer::Serialize(*scene, "Scene.json"))
			std::cout << "\nDEBUG::MESSAGE::Scene saved successfully\n";
		else
			std::cout << "\nDEBUG::ERROR::Failed to save scene\n";
    }

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
	std::cout << "\nDEBUG::MESSAGE::Switching to Editor Mode\n";

	Scene* scene = m_game.GetCurrentScene();
    scene->GetCamera().DisableCam();

    m_mode = Mode::Editor;
}

void EditorLayer::SwitchToGameMode()
{
	std::cout << "\nDEBUG::MESSAGE::Switching to Game Mode\n";
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