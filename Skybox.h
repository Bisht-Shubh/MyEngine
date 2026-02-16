#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include<iostream>

#include<vector>
#include<string>

#include "Shader.h"

class Skybox
{
private:
		unsigned int skyboxVAO, skyboxVBO;
		unsigned int cubemapTexture;
		std::vector<std::string> faces{
			"/right.jpg",
			"/left.jpg",
			"/top.jpg",
			"/bottom.jpg",
			"/front.jpg",
			"/back.jpg"
		};
		std::string directory;

public:
	// Constructors
	Skybox(const std::string& directory);
	Skybox();

	// Init skybox
	void InitSkybox();

	// Load cubemap textures
	unsigned int LoadCubemap();

	// Draw skybox
	void Draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection);

	// Destructor
	~Skybox();
};

