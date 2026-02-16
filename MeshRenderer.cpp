#include "pch.h"
#include "MeshRenderer.h"

void MeshRenderer::InitRenderData()
{
    float vertices[] = {
		// Position and texture coords
        // Front face 
        -1,-1, 1,  0,0,
         1,-1, 1,  1,0,
         1, 1, 1,  1,1,

         1, 1, 1,  1,1,
        -1, 1, 1,  0,1,
        -1,-1, 1,  0,0,

        // Back face 
         1,-1,-1,  0,0,
        -1,-1,-1,  1,0,
        -1, 1,-1,  1,1,

        -1, 1,-1,  1,1,
         1, 1,-1,  0,1,
         1,-1,-1,  0,0,

         // Left face 
         -1,-1,-1,  0,0,
         -1,-1, 1,  1,0,
         -1, 1, 1,  1,1,

         -1, 1, 1,  1,1,
         -1, 1,-1,  0,1,
         -1,-1,-1,  0,0,

         // Right face 
          1,-1, 1,  0,0,
          1,-1,-1,  1,0,
          1, 1,-1,  1,1,

          1, 1,-1,  1,1,
          1, 1, 1,  0,1,
          1,-1, 1,  0,0,

          // Top face 
          -1, 1, 1,  0,0,
           1, 1, 1,  1,0,
           1, 1,-1,  1,1,

           1, 1,-1,  1,1,
          -1, 1,-1,  0,1,
          -1, 1, 1,  0,0,

          // Bottom face 
          -1,-1,-1,  0,0,
           1,-1,-1,  1,0,
           1,-1, 1,  1,1,

           1,-1, 1,  1,1,
          -1,-1, 1,  0,1,
          -1,-1,-1,  0,0
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

MeshRenderer::MeshRenderer()
	: VAO(0), VBO(0), Width(0), Height(0)
{
}

MeshRenderer::MeshRenderer(Shader&& shader, unsigned int width, unsigned int height)
	: shader(std::move(shader)), Width(width), Height(height), VAO(0), VBO(0)
{
	this->InitRenderData();
}

MeshRenderer::~MeshRenderer()
{
	if (VAO != 0)
        glDeleteVertexArrays(1, &this->VAO);

	if (VBO != 0)
		glDeleteBuffers(1, &this->VBO);
}

MeshRenderer::MeshRenderer(MeshRenderer&& other) noexcept
  : VAO(other.VAO),
    VBO(other.VBO),
    Width(other.Width),
    Height(other.Height),
    shader(std::move(other.shader)),
    projection(other.projection)
{
    other.VAO = 0;
    other.VBO = 0;
}

MeshRenderer& MeshRenderer::operator=(MeshRenderer&& other) noexcept
{
    if (this != &other)
    {
        // clean existing resources
        if(VAO != 0)
			glDeleteVertexArrays(1, &this->VAO);

        if (VBO != 0)
            glDeleteBuffers(1, &this->VBO);

		// move resources
        VAO = other.VAO;
        VBO = other.VBO;
        Width = other.Width;
        Height = other.Height;
        shader = std::move(other.shader);
        projection = other.projection;

        // reset other's resources
        other.VAO = 0;
		other.VBO = 0;
    }

    return *this;
}

void MeshRenderer::DrawMesh()
{
	this->shader.Use();
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void MeshRenderer::Draw()
{
    this->shader.Use();
    
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
    model = glm::scale(model, glm::vec3(0.5f));
	this->shader.SetMatrix4("model", model);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void MeshRenderer::Draw(Shader& shader, Texture& texture)
{
    shader.Use();

	// Set transformations
	glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
	model = glm::scale(model, glm::vec3(0.5f));

    shader.SetMatrix4("model", model);

	// Bind texture
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

	// Draw mesh
    glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
