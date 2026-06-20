#include "Engine.h"

int main()
{
	// Screen dimensions
	unsigned int width = 1600;
	unsigned int height = 1200;

	Engine engine(width, height);
	engine.Init();

	Scene* scene = engine.GetCurrentScene();

	float cameraFOV = 45.0f;
	Camera* camera = new Camera(width, height, cameraFOV, scene->GetWindow()); 
	scene->SetCamera(camera);

	// Set properties of light
	glm::vec3 direction = glm::normalize(glm::vec3(-1.3f, -1.0f, 2.5f));
	glm::vec3 diffuse = glm::vec3(2.0f, 1.9f, 1.98f);
	glm::vec3 specular = glm::vec3(0.9, 0.7f ,0.5f);
	glm::vec3 ambient = glm::vec3(0.25f, 0.25f, 0.22f);

	// Set directional light properties and add to scene
	DirectionalLight* directionalLight = new DirectionalLight(direction, ambient, diffuse, specular);
	scene->SetDirectionalLight(direction, ambient, diffuse, specular);
	
	// Update game
	scene->SetUpdateCallback([](Scene& scene, float dt) {
		

		});

	engine.Run();

	return 0;
}