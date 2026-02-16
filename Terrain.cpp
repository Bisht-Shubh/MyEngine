
#include "pch.h"
#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::Terrain(const char* path)
	: heightMapPath(path)
{
	InitializeHeightMap();
}

void Terrain::InitializeHeightMap()
{
    stbi_set_flip_vertically_on_load(true);

	// Query maximum tessellation level supported by hardware
	glGetIntegerv(GL_MAX_TESS_GEN_LEVEL, &maxTessLevel);
	std::cout << "\nDEBUG::TERRAIN.CPP::INITIALIZE_HEIGHT_MAP()::MAX_TESSELLATION_LEVEL_SUPPORTED::" << maxTessLevel;


    glGenTextures(1, &heightMapTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightMapTexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;

    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(this->heightMapPath, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

		ResourceManager::GetShader("TessallationShader").Use().SetInteger("heightMap", 0);
        std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    std::vector<float> vertices;
    //vertices.reserve(static_cast<size_t>(this->width) * static_cast<size_t>(this->height) * 3);

    //// Map 0..255 -> -16..+16 (tweakable)
    //float yScale = 32.0f / 255.0f;
    //float yShift = 16.0f;
    //unsigned int bytePerPixel = static_cast<unsigned int>(this->nrChannels);

    //for (int i = 0; i < this->height; ++i) {
    //    for (int j = 0; j < this->width; ++j) {
    //        size_t idx = (static_cast<size_t>(i) * static_cast<size_t>(this->width) + static_cast<size_t>(j)) * bytePerPixel;
    //        unsigned char* pixelOffset = data + idx;
    //        unsigned char y = pixelOffset[0];

    //        float vx = -static_cast<float>(this->height) / 2.0f + static_cast<float>(i);
    //        float vy = static_cast<float>(y) * yScale - yShift;
    //        float vz = -static_cast<float>(this->width) / 2.0f + static_cast<float>(j);

    //        vertices.push_back(vx);
    //        vertices.push_back(vy);
    //        vertices.push_back(vz);
    //    }
    //}

    for (unsigned i = 0; i < rez - 1; i++)
    {
        for (unsigned j = 0; j < rez - 1; j++)
        {
            vertices.push_back(-width / 2.0f + width * i / (float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height / 2.0f + height * j / (float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            vertices.push_back(-width / 2.0f + width * (i + 1) / (float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height / 2.0f + height * j / (float)rez); // v.z
            vertices.push_back((i + 1) / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            vertices.push_back(-width / 2.0f + width * i / (float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height / 2.0f + height * (j + 1) / (float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back((j + 1) / (float)rez); // v

            vertices.push_back(-width / 2.0f + width * (i + 1) / (float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height / 2.0f + height * (j + 1) / (float)rez); // v.z
            vertices.push_back((i + 1) / (float)rez); // u
            vertices.push_back((j + 1) / (float)rez); // v
        }
    }

    std::cout << "\nDEBUG::TERRAIN.CPP::INITIALIZE_HEIGHT_MAP()::HEIGHT_MAP_LOADED_WITH::" << rez * rez << "::PATCHES_OF_4_CONTROL_POINTS_EACH" << std::endl;
    std::cout << "\nDEBUG::TERRAIN.CPP::INITIALIZE_HEIGHT_MAP()::HEIGHT_MAP_LOADED_WITH::" << rez * rez * 4 << "::VERTICES_IN_VERTEX_SHADER" << std::endl;
   

    // Compute index/strip counts deterministically and store to members
    // number of vertical strips = number of i-iterations in indices loop
    //unsigned int strips = 0;
    //if (rez > 0 && this->height > 1)
    //    strips = static_cast<unsigned int>((this->height - 1) / rez);
    //else
    //    strips = 0;

    //// columns per strip (how many j steps)
    //unsigned int colsPerStrip = 0;
    //if (rez > 0 && this->width > 0)
    //    colsPerStrip = static_cast<unsigned int>((this->width + rez - 1) / rez);
    //else
    //    colsPerStrip = 0;

    //unsigned int indicesPerStrip = 2 * colsPerStrip;               // two indices per column (i and i+rez)
    //unsigned int trisPerStrip = (indicesPerStrip >= 2) ? (indicesPerStrip - 2) : 0;

    //this->numStrips = strips;
    //this->numTrisPerStrip = trisPerStrip;

    //std::vector<unsigned> indices;
    //indices.reserve(static_cast<size_t>(strips) * indicesPerStrip);

    //for (unsigned i = 0; i < static_cast<unsigned>(this->height - 1); i += rez)
    //{
    //    for (unsigned j = 0; j < static_cast<unsigned>(this->width); j += rez)
    //    {
    //        // push two indices per column for triangle strip (i,j) and (i+rez,j)
    //        indices.push_back(j + this->width * i);
    //        indices.push_back(j + this->width * (i + rez));
    //    }
    //}

    //std::cout << "\nDEBUG::TERRAIN.CPP::INITIALIZE_HEIGHT_MAP()::HEIGHT_MAP_LOADED_WITH::" << indices.size() << "::INDICES";
    //std::cout << "\nDEBUG::TERRAIN.CPP::INITIALIZE_HEIGHT_MAP()::HEIGHT_MAP_LOADED_WITH::" << this->numStrips << "::STRIPS::" << "AND::" << this->numTrisPerStrip << "::TRIANGLES_EACH.";

    // Create and bind VAO/VBO/IBO correctly so attribute and element bindings are stored in the VAO
    //glGenVertexArrays(1, &terrainVAO);
    //glGenBuffers(1, &terrainVBO);
    //glGenBuffers(1, &terrainIBO);

    //glBindVertexArray(terrainVAO);

    //glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    //// position attribute
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //// element buffer must be bound while VAO is bound
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);

    //// unbind VAO (optional)
    //glBindVertexArray(0);

    // Create and bind VAO/VBO correctly so attribute and element bindings are stored in the VAO
	glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);

    glGenBuffers(1, &terrainVBO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glPatchParameteri(GL_PATCH_VERTICES, NUM_PATCH_PTS);
}

void Terrain::Draw()
{
    // Prepare transformations
	glm::mat4 model{ glm::mat4(1.0f) };
	ResourceManager::GetShader("TessallationShader").Use().SetMatrix4("model", model);

	// Render 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightMapTexture);

	glBindVertexArray(terrainVAO);
    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawArrays(GL_PATCHES, 0, (rez - 1) * (rez - 1) * 4);
	//glDrawArrays(GL_PATCHES, 0, rez * rez * NUM_PATCH_PTS);
}

Terrain::~Terrain()
{
	glDeleteVertexArrays(1, &terrainVAO);
	glDeleteBuffers(1, &terrainVBO);
	//glDeleteBuffers(1, &terrainIBO);
}

