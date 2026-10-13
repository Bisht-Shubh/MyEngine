//Load mesh when doing model loading

#pragma once
#include "pch.h"
#include<glad/glad.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include<string>
#include<vector>

#include "BoundingBox.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture_Mesh {
	unsigned int ID;
	std::string type;
	std::string path;
};

class Mesh
{
private:
	unsigned int VBO, EBO;
	int m_vertexCount, m_indexCount;
	void setupMesh();

	BoundingBox m_LocalBounds;
	void CalculateBounds();

public:
	unsigned int VAO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture_Mesh> textures;
	glm::vec3 color; // per-mesh material color (used when no texture)

	BoundingBox GetLocalBounds() const;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture_Mesh> textures, const glm::vec3& color);
	void draw(Shader& shader);
	//~Mesh();
};
