#include "pch.h"
#include "ResourceManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include<assert.h>

#include "stbi_image.h"
std::map<std::string, Texture>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;


Shader& ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    // load shader from the files
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile, name);

    return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Shader& ResourceManager::LoadTessellationShader(const char* vShaderFile, const char* tcShaderFile, const char* teShaderFile, const char* fShaderFile, std::string name)
{
	Shaders[name] = loadTessellationShaderFromFile(vShaderFile, tcShaderFile, teShaderFile, fShaderFile);
	return Shaders[name];
}

Texture& ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture& ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
	Shaders.clear();
	Textures.clear();
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        // check if vertex shader file opens successfully 
        if (!vertexShaderFile)
        {
            std::cerr << "\nERROR::SHADER::Failed to open vertex shader\n"
                << "PATH::" << vShaderFile;

            assert(false);
        }

        std::ifstream fragmentShaderFile(fShaderFile);
        // check if fragment shader file opens succesfully
        if (!fragmentShaderFile)
        {
            std::cerr << "\nERROR::SHADER::Failed to open fragment shader\n"
                << "PATH::" << fShaderFile;

            assert(false);
        }

        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files::" << "SHADER_NAME::" << name << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
    // create texture object
    Texture texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}

Shader ResourceManager::loadTessellationShaderFromFile(const char* vShaderFile, const char* tcShaderFile, const char* teShaderFile, const char* fShaderFile)
{
	// 1. retrieve the vertex/tessellation control/tessellation evaluation/fragment source code from filePath
	std::string vertexCode;
	std::string tessControlCode;
	std::string tessEvalCode;
	std::string fragmentCode;

    // open files
    std::ifstream vertexShaderFile(vShaderFile);
    std::ifstream tessControlShaderFile(tcShaderFile);
    std::ifstream tessEvalShaderFile(teShaderFile);
    std::ifstream fragmentShaderFile(fShaderFile);

	// Check for errors
    if (!vertexShaderFile || !tessControlShaderFile ||
        !tessEvalShaderFile || !fragmentShaderFile)
    {
        std::cout << "\nERROR::SHADER::FAILED_TO_LOAD_TESSALLATION_SHADER" << std::endl;
        return Shader();
	}

    std::stringstream vShaderStream, tcShaderStream, teShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vertexShaderFile.rdbuf();
    tcShaderStream << tessControlShaderFile.rdbuf();
    teShaderStream << tessEvalShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();
    // close file handlers
    vertexShaderFile.close();
    tessControlShaderFile.close();
    tessEvalShaderFile.close();
    fragmentShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    tessControlCode = tcShaderStream.str();
    tessEvalCode = teShaderStream.str();
    fragmentCode = fShaderStream.str();
    

	const char* vShaderCode = vertexCode.c_str();
	const char* tcShaderCode = tessControlCode.c_str();
	const char* teShaderCode = tessEvalCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2. now create shader object from source code
	Shader shader;
	shader.CompileTessellation(vShaderCode, tcShaderCode, teShaderCode, fShaderCode);
    
    return shader;
}
