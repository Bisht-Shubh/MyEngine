#include "pch.h"
#include "Shader.h"

Shader::Shader() : ID(0) {}

Shader::~Shader()
{
    if (ID != 0)
    {
        glDeleteProgram(ID);
		ID = 0; 
    }
}

Shader::Shader(Shader&& other) noexcept
    : ID(other.ID)
{
	other.ID = 0; // Prevent other from deleting resource
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    if (this != &other)
    {
        if (ID != 0)
			glDeleteProgram(ID); // Clean up existing resource

		// Transfer ownership of resource
        ID = other.ID;
		other.ID = 0;
    }

    return *this;
}

Shader& Shader::Use()
{
    glUseProgram(this->ID);
    return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    unsigned int sVertex, sFragment, gShader;
    // vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    // shader program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->ID, gShader);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void Shader::CompileTessellation(const char* vertexSource, const char* tessControlSource, const char* tessEvalSource, const char* fragmentSource)
{
	// Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	// Tessellation Control Shader
	GLuint tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(tessControlShader, 1, &tessControlSource, NULL);
	glCompileShader(tessControlShader);
	checkCompileErrors(tessControlShader, "TESS_CONTROL");

	// Tessellation Evaluation Shader
	GLuint tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(tessEvalShader, 1, &tessEvalSource, NULL);
	glCompileShader(tessEvalShader);
	checkCompileErrors(tessEvalShader, "TESS_EVALUATION");

	// Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");

	// Shader Program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexShader);
	glAttachShader(this->ID, tessControlShader);
	glAttachShader(this->ID, tessEvalShader);
	glAttachShader(this->ID, fragmentShader);
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");

    // Delete shaders after linking
    glDeleteShader(vertexShader);
	glDeleteShader(tessControlShader);
	glDeleteShader(tessEvalShader);
	glDeleteShader(fragmentShader);
}

void Shader::SetBool(const char* name, bool value, bool useShader)
{
    if (useShader)
        this->Use();
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetFloat(const char* name, float value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetInteger(const char* name, int value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetVector2f(const char* name, float x, float y, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
{
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}


void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}