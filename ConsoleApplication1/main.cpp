#include "Engine.h"

int main()
{
	// Screen dimensions
	unsigned int width = 800;
	unsigned int height = 600;

	Engine engine(width, height);
	engine.Init();

	Scene* scene = engine.GetCurrentScene();

	float cameraFOV = 45.0f;
	Camera* camera = new Camera(width, height, cameraFOV, scene->GetWindow()); 
	scene->SetCamera(camera);

	Cube* cube1 = scene->Instantiate();
	cube1->position = glm::vec3(0.0f, 0.0f, -4.0f);

	Cube* cube2 = scene->Instantiate();
	cube2->position = glm::vec3(6.0f, 0.0f, -4.0f);

	scene->SetUpdateCallback([](Scene& scene, float dt) {

		static float speed = 4.0f;
		static float rotationSpeed = 100.0f;

		for (MeshRenderer* gameObject : scene.gameObjects)
		{	
			gameObject->position.y += -speed * dt;
			gameObject->rotation.z += rotationSpeed * dt;
		}
		});

	engine.Run();

	return 0;
}