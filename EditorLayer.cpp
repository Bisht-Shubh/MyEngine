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
#include "RayCaster.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <string>


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


    if (m_input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        Ray ray = RayCaster::CreateRay(m_input.GetMouseX(), m_input.GetMouseY(), scene->Width, scene->Height,
            scene->GetCamera().GetView(), scene->GetCamera().GetProjection(), scene->GetCamera().GetCameraPos());

        std::optional<decltype(
            scene->GetEntityManager().GetAllEntities().front().id)> closestEntityID;
        float closestDistance = (std::numeric_limits<float>::max)();

        for (const EntityData& data : scene->GetEntityManager().GetAllEntities())
        {
            Entity entity = scene->GetEntityManager().GetEntity(data.id);
            auto* renderer = entity.GetComponent<MeshRenderer>();
            auto* transform = entity.GetComponent<Transform>();

            if (!renderer || !transform)
                continue;

            BoundingBox localBounds = renderer->GetModel()->GetLocalBounds();

            float distance{ 0.0f };

            glm::mat4 modelMatrix = transform->GetModelMatrix();
            BoundingBox worldBounds = TransformBoundingBox(localBounds, modelMatrix);

            if (RayCaster::IntersectsAABB(ray, worldBounds.min, worldBounds.max, distance) && distance < closestDistance)
            {
                closestDistance = distance;
                closestEntityID = data.id;
            }

        }

        if (closestEntityID.has_value())
        {
            m_selectedEntityID = *closestEntityID;

            Entity hitEntity =
                scene->GetEntityManager().GetEntity(*m_selectedEntityID);

            std::cout << "Entity \""
                << hitEntity.GetName()
                << "\" hit\n";
        }
    }
    
    if (m_selectedEntityID.has_value())
    {
        Entity entity = scene->GetEntityManager().GetEntity(*m_selectedEntityID);

        Transform* transform = entity.GetComponent<Transform>();

        if (transform)
        {
            ImGui::Begin(entity.GetName().c_str());

            glm::vec3 position = transform->GetPosition();
            if (ImGui::DragFloat3("Position", &position.x, 0.1f))
                transform->SetPosition(position);

            glm::vec3 rotation = transform->GetRotation();
            if (ImGui::DragFloat3("Rotation", &rotation.x, 0.5f))
                transform->SetRotation(rotation);

            glm::vec3 scale = transform->GetScale();
            if (ImGui::DragFloat3("Scale", &scale.x, 0.1f))
                transform->SetScale(scale);

            ImGui::End();
        }
    }


	//Transform Inspector

	ImGui::Begin("Inspector");

    for (const EntityData& entityData : scene->GetEntityManager().GetAllEntities())
    {
        Entity entity = scene->GetEntityManager().GetEntity(entityData.id);
        Transform* transform = entity.GetComponent<Transform>();


        if (!transform)
            continue;

        ImGui::PushID(static_cast<int>(entityData.id));

        if (ImGui::TreeNode(entityData.name.c_str()))
        {
            // Position
            glm::vec3 position = transform->GetPosition();
            if (ImGui::DragFloat3("Position", &position.x, 0.1f))
                transform->SetPosition(position);

            // Rotation
            glm::vec3 rotation = transform->GetRotation();
            if (ImGui::DragFloat3("Rotation", &rotation.x, 0.5f))
                transform->SetRotation(rotation);

            // Scale
            glm::vec3 scale = transform->GetScale();
            if (ImGui::DragFloat3("Scale", &scale.x, 0.1f))
                transform->SetScale(scale);

            ImGui::TreePop();
        }
        ImGui::PopID();


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