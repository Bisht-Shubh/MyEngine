#pragma once
#define GLM_ENABLE_EXPERIMENTAL


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Shader.h"
#include "Texture.h"

class MeshRenderer
{
protected:
	// Vertex attributes 
	unsigned int VAO;
	unsigned int VBO;
	unsigned int Width, Height;

	// Shader (non-owning)
	Shader* shader;

	// Render data
	glm::mat4 projection;

	// Init Render data
	virtual void InitRenderData() = 0;

public:
	// Transformations
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	// Set view and projection matrices
	virtual void SetViewProjection(const glm::mat4& view, const glm::mat4& projection);

	// Constructor
	MeshRenderer();
	MeshRenderer(Shader& shader, unsigned int width, unsigned int height);

	// Destructor
	~MeshRenderer();

	// Prevent copying
	MeshRenderer(const MeshRenderer&) = delete;
	MeshRenderer& operator=(const MeshRenderer&) = delete;

	// Enable move semantics
	MeshRenderer(MeshRenderer&& other) noexcept;
	MeshRenderer& operator=(MeshRenderer&& other) noexcept;

	void SetView(const glm::mat4& view);
	void SetProjection(const glm::mat4& projection);

	// Render mesh
	virtual void DrawMesh() = 0;
	virtual void Draw();
	virtual void Draw(Shader& shader, Texture& texture);
};

