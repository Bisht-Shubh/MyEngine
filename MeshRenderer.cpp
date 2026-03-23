#include "pch.h"
#include "MeshRenderer.h"

void MeshRenderer::SetViewProjection(const glm::mat4& view, const glm::mat4& projection)
{
	SetView(view);
	SetProjection(projection);
}

MeshRenderer::MeshRenderer()
	: VAO(0), VBO(0), Width(0), Height(0), shader(nullptr)
{
}

MeshRenderer::MeshRenderer(Shader& shader, unsigned int width, unsigned int height)
	:  shader(&shader), VAO(0), VBO(0), Width(width), Height(height)
{

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
	  shader(other.shader),
	  projection(other.projection)
{
	other.VAO = 0;
	other.VBO = 0;
	other.shader = nullptr;
}

MeshRenderer& MeshRenderer::operator=(MeshRenderer&& other) noexcept
{
	if (this != &other)
	{
		if (VAO != 0)
			glDeleteVertexArrays(1, &this->VAO);

		if (VBO != 0)
			glDeleteBuffers(1, &this->VBO);

		VAO = other.VAO;
		VBO = other.VBO;
		Width = other.Width;
		Height = other.Height;
		shader = other.shader;
		projection = other.projection;

		other.VAO = 0;
		other.VBO = 0;
		other.shader = nullptr;
	}

	return *this;
}

void MeshRenderer::SetView(const glm::mat4& view)
{
	if (!shader)
		return;

	shader->Use();
	shader->SetMatrix4("view", view);
}

void MeshRenderer::SetProjection(const glm::mat4& projection)
{
	if (!shader)
		return;

	shader->Use();
	shader->SetMatrix4("projection", projection);
}

void MeshRenderer::Draw()
{
	if (!shader)
		return;

	shader->Use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
	model = glm::scale(model, glm::vec3(0.5f));
	shader->SetMatrix4("model", model);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void MeshRenderer::Draw(Shader& shader, Texture& texture)
{
	shader.Use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetMatrix4("model", model);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
