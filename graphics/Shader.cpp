#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <direct.h>
#define GetCurrentDir _getcwd

#include <glm/gtc/type_ptr.hpp>

void Shader::compile(std::string vertexCode, std::string fragmentCode, std::string geometryCode)
{
	// Compile shaders
	unsigned int vertex, fragment, geometry;
	int success;
	char infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexCodeCstr = vertexCode.c_str();
	glShaderSource(vertex, 1, &vertexCodeCstr, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentCodeCstr = fragmentCode.c_str();
	glShaderSource(fragment, 1, &fragmentCodeCstr, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

    if(!geometryCode.empty())
    {
        // Geometry Shader
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        const char *geometryCodeCstr = geometryCode.c_str();
        glShaderSource(geometry, 1, &geometryCodeCstr, NULL);
        glCompileShader(geometry);

        glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(geometry, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
    }

	// Create Shader Program
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
    if(!geometryCode.empty())
        glAttachShader(id, geometry);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if(!success)
	{
	    glGetProgramInfoLog(id, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Cleanup
	glDeleteShader(vertex);
	glDeleteShader(fragment);
    if(!geometryCode.empty())
        glDeleteShader(geometry);
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
		                                    glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, glm::vec4 value) const
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

