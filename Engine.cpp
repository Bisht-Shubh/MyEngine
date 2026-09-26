#include "pch.h"
#include "Engine.h"

void PrintShaderList();

Engine::Engine(Input& input)
    : m_input(input)
{
}

Engine::~Engine()
{
    m_currentScene.reset();
}

void Engine::Init()
{
    LoadResources();

    m_currentScene = std::make_unique<Scene>(1400, 1200, m_input);

    m_currentScene->Init();

    Entity car = m_currentScene->CreateEntity("Car");

    MeshRenderer* meshRenderer = car.AddComponent<MeshRenderer>();

    Model* carModel = new Model("Assets/Models/Low Poly Car.obj");

    meshRenderer->SetModel(carModel);

    Material* carMaterial = new Material(&ResourceManager::GetShader("SpotLight"));

    meshRenderer->SetMaterial(carMaterial);

    Transform* carTransform = car.AddComponent<Transform>();

    carTransform->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));

    car.AddComponent<SpotLight>();
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
    if (!m_currentScene)
        return;

    m_cameraController.Update(deltaTime, m_currentScene->GetCamera(), m_input);
}

void Engine::Render()
{
    if (!m_currentScene)
        return;

    m_renderer.Render(*m_currentScene);
}

void Engine::LoadScene(Scene* newScene)
{
    if (!newScene)
        return;

    m_currentScene.reset();

    m_currentScene = std::make_unique<Scene>(newScene->Width, newScene->Height, m_input);

    m_currentScene->Init();
}

Scene* Engine::GetCurrentScene() const
{
    return m_currentScene.get();
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
    ss << "\nLOADED_SHADERS::("<< ResourceManager::Shaders.size() << ")\n";
    ss << "\n--------------------------------------------\n";

    for (const auto& [name, shader]
        : ResourceManager::Shaders)
    {
        ss << name << "\n";
    }

    ss << "============================================\n";

    std::cout << ss.str();
}