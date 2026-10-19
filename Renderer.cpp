#include "pch.h"
#include "Renderer.h"
#include "Entity.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "DirectionalLight.h"


void Renderer::Render(Scene& scene)
{
    glViewport(0, 0, scene.Width, scene.Height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Camera& camera = scene.GetCamera();
    EntityManager& entityManager = scene.GetEntityManager();

    // PASS 1: Collect all lights, including light-only entities.
    std::vector<SpotLight*> spotLights;
    std::vector<PointLight*> pointLights;
    std::vector<DirectionalLight*> directionalLights;

    for (const EntityData& data : entityManager.GetAllEntities())
    {
        Entity entity = entityManager.GetEntity(data.id);

        if (auto* light = entity.GetComponent<SpotLight>())
            spotLights.push_back(light);

        if (auto* light = entity.GetComponent<PointLight>())
            pointLights.push_back(light);

        if (auto* light = entity.GetComponent<DirectionalLight>())
            directionalLights.push_back(light);
    }

    // Match the GLSL array capacities.
    const int spotCount =
        std::min(static_cast<int>(spotLights.size()), 8);
    const int pointCount =
        std::min(static_cast<int>(pointLights.size()), 16);
    const int directionalCount =
        std::min(static_cast<int>(directionalLights.size()), 4);

    // PASS 2: Render entities.
    for (const EntityData& data : entityManager.GetAllEntities())
    {
        Entity entity = entityManager.GetEntity(data.id);

        Transform* transform = entity.GetComponent<Transform>();
        MeshRenderer* meshRenderer = entity.GetComponent<MeshRenderer>();

        if (!transform || !meshRenderer)
            continue;

        Model* model = meshRenderer->GetModel();
        Material* material = meshRenderer->GetMaterial();

        if (!model || !material)
            continue;

        Shader* shader = material->GetShader();

        if (!shader)
            continue;

        shader->Use();

        // Upload all lights to this material's shader.
        for (int i = 0; i < spotCount; ++i)
            spotLights[i]->ApplyLight(*shader, i);

        shader->SetInteger("numSpotLights", spotCount);

        for (int i = 0; i < pointCount; ++i)
            pointLights[i]->ApplyLight(*shader, i);

        shader->SetInteger("numPointLights", pointCount);

        for (int i = 0; i < directionalCount; ++i)
            directionalLights[i]->ApplyLight(*shader, i);

        shader->SetInteger(
            "numDirectionalLights", directionalCount);

        // Matrices.
        shader->SetMatrix4(
            "model", transform->GetModelMatrix());

        // Motion blur
        // Adding previous model uniforms to positions
        shader->SetMatrix4("previousModel", transform->GetPreviousModelMatrix());

        shader->SetMatrix4(
            "view", camera.GetView());

        shader->SetMatrix4(
            "projection", camera.GetProjection());

        model->Draw(*shader);
    }

    //-------------------TODO-------------------//
    // PASS 3 : Velocity Pass : Motion Blur
    //for (const EntityData& data : entityManager.GetAllEntities())
    //{
    //    Entity entity = entityManager.GetEntity(data.id);

    //    if (auto* transform = entity.GetComponent<Transform>())
    //        transform->CommitPreviousTransform();
    //}
}
