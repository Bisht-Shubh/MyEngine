#pragma once
#include "pch.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "stbi_image.h"
#include <string>
#include <vector>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
private:

	
	void loadModel(std::string path);
	void processNodes(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture_Mesh> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	std::vector<Texture_Mesh> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	Model(const char* path)
	{
		loadModel(path);
	}
	void Draw(Shader& shader);
};

