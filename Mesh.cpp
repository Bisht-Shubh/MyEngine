#include "pch.h"
#include "Mesh.h"

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::CalculateBounds()
{
    const float maxFloat = std::numeric_limits<float>::max();

    m_LocalBounds.minPoint = glm::vec3(maxFloat);
    m_LocalBounds.maxPoint = glm::vec3(
        std::numeric_limits<float>::lowest());

    for (const Vertex& vertex : vertices)
    {
        m_LocalBounds.minPoint =
            glm::min(m_LocalBounds.minPoint, vertex.Position);

        m_LocalBounds.maxPoint =
            glm::max(m_LocalBounds.maxPoint, vertex.Position);
    }
}

BoundingBox Mesh::GetLocalBounds() const
{
    return m_LocalBounds;   
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture_Mesh> textures, const glm::vec3& color)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    this->color = color;
    CalculateBounds();
    setupMesh();
}

void Mesh::draw(Shader& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;

    // ensure shader is active and set material properties
    shader.Use();
    shader.SetBool("useTexture", textures.size() > 0);
    shader.SetVector3f("materialColor", this->color);

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        const std::string name = textures[i].type;

        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        if (name == "texture_specular")
            number = std::to_string(specularNr++);
        if (name == "texture_normal")
            number = std::to_string(normalNr++);

        shader.SetInteger((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].ID);
    }

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
