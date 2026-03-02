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

	MeshRenderer* cube = scene->Instantiate();

	engine.Run();

	return 0;
}