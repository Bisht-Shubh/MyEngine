#include "pch.h"
#include "Cube.h"

Cube::Cube()
	: MeshRenderer()
{
}

Cube::Cube(Shader& shader, unsigned int width, unsigned int height)
	: MeshRenderer(shader, width, height)
{
	this->InitRenderData();
	position = glm::vec3(0.0f, 0.0f, -4.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

void Cube::DrawMesh()
{
	if (!shader)
		return;

	shader->Use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);
	shader->SetMatrix4("model", model);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Cube::SetViewProjection(const glm::mat4& view, const glm::mat4& projection)
{
	SetView(view);
	SetProjection(projection);
}

void Cube::InitRenderData()
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


