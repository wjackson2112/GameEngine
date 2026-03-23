//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//https://learnopengl.com/Getting-started/Shaders

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	// The program ID
	unsigned int id;

	// Constructor reads and builds the shader
//	Shader() = default;
//	Shader(const char* vertexPath, const char* fragmentPath);

	// Use/Activate the shader
    void compile(std::string vertexCode, std::string fragmentCode, std::string geometryCode);
	void use();

	// Utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4 value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, glm::vec4) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
};

#endif
