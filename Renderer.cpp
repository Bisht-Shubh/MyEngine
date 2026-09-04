#include "pch.h"
#include "Renderer.h"
#include "Entity.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "SpotLight.h"


void Renderer::Render(Scene& scene)
{
    // --------------------------------------------------
    // Frame setup
    // --------------------------------------------------
    glViewport(0, 0, scene.Width, scene.Height);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Camera& camera = scene.GetCamera();
    EntityManager& entityManager = scene.GetEntityManager();

    // --------------------------------------------------
    // Render entities
    // --------------------------------------------------
    for (const EntityData& data : entityManager.GetAllEntities())
    {
        Entity entity = entityManager.GetEntity(data.id);

        Transform* transform = entity.GetComponent<Transform>();
        MeshRenderer* meshRenderer = entity.GetComponent<MeshRenderer>();
        SpotLight* spotlight = entity.GetComponent<SpotLight>();

        // Entity must have the components required for rendering
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

        // --------------------------------------------------
        // Lighting
        // --------------------------------------------------
        if (spotlight)
        {
            spotlight->ApplyLight(*shader);
        }

        // --------------------------------------------------
        // Matrices
        // --------------------------------------------------
        shader->SetMatrix4(
            "model",
            transform->GetModelMatrix()
        );

        shader->SetMatrix4(
            "view",
            camera.GetView()
        );

        shader->SetMatrix4(
            "projection",
            camera.GetProjection()
        );

        // --------------------------------------------------
        // Draw
        // --------------------------------------------------
        model->Draw(*shader);
    }
}