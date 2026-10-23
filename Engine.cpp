#include "pch.h"
#include "Engine.h"

#include "imGuiLayer.h"
#include "Scene.h"
#include "ResourceManager.h"
#include <chrono>

void PrintShaderList();

Engine::Engine(Input& input, imGuiLayer& imguiLayer)
                        : m_input(input), m_debugLayer(), m_game(input), m_editorLayer(m_game, m_input, m_debugLayer, imguiLayer),
                                    m_imguiLayer(imguiLayer)
{
}

Engine::~Engine() = default;

void Engine::Init()
{
    LoadResources();

    m_game.Init();
}

void Engine::LoadResources()
{
    auto start = std::chrono::high_resolution_clock::now();

    ResourceManager::LoadShader("Shader Files/SpotLight_vs.txt", "Shader Files/SpotLight_fs.txt", nullptr, "SpotLight");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<float, std::milli>(end - start);
    m_debugLayer.SetShaderLoadTime(static_cast<int>(duration.count()));

    PrintShaderList();
}

void Engine::Update(float deltaTime)
{
    m_editorLayer.CheckInput();

    //if (m_editorLayer.IsEditorMode())
    //    m_editorLayer.Update(deltaTime);

    //else
    //    m_game.Update(deltaTime);

    m_editorLayer.Update(deltaTime);

    if(m_editorLayer.IsGameMode())
        m_game.Update(deltaTime);
}

void Engine::Render()
{
    Scene* scene = m_game.GetCurrentScene();

   if(scene)
	   m_renderer.Render(*scene);

   //if (m_editorLayer.IsEditorMode())
       m_imguiLayer.Render();
}

DebugLayer& Engine::GetDebugLayer()
{
    return m_debugLayer;
}

void PrintShaderList()
{
    std::stringstream ss;

    ss << "\n============================================\n";
    ss << "DEBUG::Shader loading complete";

    ss << "\nLOADED_SHADERS::("
        << ResourceManager::Shaders.size()
        << ")\n";

    ss << "\n--------------------------------------------\n";

    for (const auto& [name, shader] : ResourceManager::Shaders)
    {
        ss << name << "\n";
    }

    ss << "============================================\n";

    std::cout << ss.str();
}