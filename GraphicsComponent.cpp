#include "GraphicsComponent.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>

#include "stb_image.h"

#include "Transform.h"
#include "PhysicsComponent.h"
#include "Entity.h"

GraphicsComponent::GraphicsComponent(Vertex* vertices, unsigned int numVerts, unsigned int* indices,
                                     unsigned int numInds, std::string vertexShaderPath,
                                     std::string fragmentShaderPath, std::string diffusePath,
                                     std::string specularPath)
{
//    this->shader = Shader(vertexShaderPath.c_str(),
//                        fragmentShaderPath.c_str());

	for(int i = 0; i < numVerts; i++)
		this->vertices.push_back(vertices[i]);

	for(int i = 0; i < numInds; i++)
		this->indices.push_back(indices[i]);

	diffuseTexture = loadTexture(diffusePath);
	specularTexture = loadTexture(specularPath);
	configureVAO();
}

GraphicsComponent::~GraphicsComponent()
{
	this->vertices.clear();
	this->indices.clear();
}

void GraphicsComponent::configureVAO()
{
	unsigned int VBO, EBO;

	// Create Vertex Array Object
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// Create Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	Vertex vertArray[this->vertices.size()];
	std::copy(this->vertices.begin(), this->vertices.end(), vertArray);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), vertArray, GL_STATIC_DRAW);

	// Create Element Buffer Object
	// glGenBuffers(1, &EBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->numInds, this->indices, GL_STATIC_DRAW);

	// Set up vertex attributes for shader input
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	// glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

unsigned int GraphicsComponent::loadTexture(std::string texturePath)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	
	int width, height, nrChannels;
	unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if(data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	return textureID;
}

// https://learnopengl.com/Getting-started/Hello-Triangle
void GraphicsComponent::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos)
{
    Transform transform = parent->getWorldTransform();
    this->shader.use();

	glBindVertexArray(this->VAO);

	shader.setInt("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->diffuseTexture); 
	
	shader.setInt("material.specular", 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->specularTexture);
	

	shader.setMat4("model", transform.getModel());
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	// shader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
	shader.setVec3("light.direction", lightDir.x, lightDir.y, lightDir.z);
	shader.setVec3("viewPos", viewPos.x, viewPos.y, viewPos.z);

	// shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	shader.setFloat("material.shininess", 32.0f);

	shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}