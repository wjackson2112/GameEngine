#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include <vector>

#include "Component.h"
#include "Shader.h"
#include "Mesh.h"

class GraphicsComponent : public Component 
{
    Shader shader;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int diffuseTexture;
	unsigned int specularTexture;
    unsigned int VAO;

	unsigned int loadTexture(std::string texturePath);
	void configureVAO();

    // Component Interface
public:
    GraphicsComponent() {}
    GraphicsComponent(Vertex* vertices, unsigned int numVerts, unsigned int* indices,
		   	   unsigned int numInds, std::string vertexShaderPath,
		   	   std::string fragmentShaderPath, std::string diffusePath,
			   std::string specularPath);

    ~GraphicsComponent();

    void update(float deltaTime) override {};
    void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos);

    // End Component Interface
};

#endif //GRAPHICS_COMPONENT_H