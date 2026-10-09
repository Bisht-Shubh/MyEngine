//set shader code and generate matrices

#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Shader
{
public:
    // state
    unsigned int ID;

    // constructor
    Shader();

	// Destructor
	~Shader();

    // disable copy constructor
	Shader(const Shader&) = delete; 

    // disable copy assignment operator
	Shader& operator=(const Shader&) = delete; 

	// move constructor
    Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

    // sets the current shader as active
    Shader& Use();

    // compiles the shader from given source code
    void    Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); // note: geometry source code is optional 

	// compiles tessellation shaders
	void CompileTessellation(const char* vertexSource, const char* tessControlSource, const char* tessEvalSource, const char* fragmentSource);

    // utility functions
    // overloads accepting const char*
    void    SetBool(const char* name, bool value, bool useShader = false);
    void    SetFloat(const char* name, float value, bool useShader = false);
    void    SetInteger(const char* name, int value, bool useShader = false);
    void    SetVector2f(const char* name, float x, float y, bool useShader = false);
    void    SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);
    void    SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
    void    SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);
    void    SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
    void    SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);
    void    SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);

    // overloads accepting std::string to avoid calling .c_str() at call sites
    void    SetBool(const std::string& name, bool value, bool useShader = false);
    void    SetFloat(const std::string& name, float value, bool useShader = false);
    void    SetInteger(const std::string& name, int value, bool useShader = false);
    void    SetVector2f(const std::string& name, float x, float y, bool useShader = false);
    void    SetVector2f(const std::string& name, const glm::vec2& value, bool useShader = false);
    void    SetVector3f(const std::string& name, float x, float y, float z, bool useShader = false);
    void    SetVector3f(const std::string& name, const glm::vec3& value, bool useShader = false);
    void    SetVector4f(const std::string& name, float x, float y, float z, float w, bool useShader = false);
    void    SetVector4f(const std::string& name, const glm::vec4& value, bool useShader = false);
    void    SetMatrix4(const std::string& name, const glm::mat4& matrix, bool useShader = false);
private:
    // checks if compilation or linking failed and if so, print the error logs
    void    checkCompileErrors(unsigned int object, std::string type);
};
