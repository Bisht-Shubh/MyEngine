#pragma once

#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<vector>

#include "ResourceManager.h"
#include "stbi_image.h"

// Terrain class for procedural generation of landscapes

class Terrain
{
private:
	// Height map properties
	int width{0}, height{0}, nrChannels{0};
	const char* heightMapPath{nullptr};
	unsigned int heightMapTexture;

	// OpenGL buffers
	unsigned int terrainVBO{0}, terrainIBO{0}, terrainVAO{0};

	// Level of detail properties
	unsigned rez{ 20 }; // Level of detail

	// Compute/assign these at runtime in InitializeHeightMap()
	int numStrips{0};
	int numTrisPerStrip{0};
	const unsigned int NUM_PATCH_PTS = 4;

	// Tessellation properties
	GLint maxTessLevel;

public:
	// Constructors
	Terrain();
	Terrain(const char* path);

	// Initialize height map from file
	void InitializeHeightMap();

	// Draw terrain
	void Draw();

	// Destructor
	~Terrain();
};

