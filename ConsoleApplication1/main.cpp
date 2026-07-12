#include "Engine.h"

int main()
{
	Engine engine;
	engine.Init();

	Scene* scene = engine.GetCurrentScene();

	//float cameraFOV = 45.0f;
	//Camera* camera = new Camera(width, height, cameraFOV, Wi); 
	//scene->SetCamera(camera); 
	
	// Update game
	scene->SetUpdateCallback([](Scene& scene, float dt) {
		

		});

	engine.Run();

	return 0;
}