//
// Created by Will on 6/5/2022.
//

#include <glad/glad.h>

#include "Transform.h"
#include "ModelComponent.h"
#include "Model.h"

#include "Entity.h"

ModelComponent::ModelComponent(std::string path, std::string vertexShaderPath, std::string fragmentShaderPath)
: model(Model(path))
, shader(Shader()){}

//void ModelComponent::configureVAO()
//{
//    unsigned int VBO, EBO;
//
//    // Create Vertex Array Object
//    glGenVertexArrays(1, &this->VAO);
//    glBindVertexArray(this->VAO);
//
//    // Create Vertex Buffer Object
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    Vertex vertArray[this->vertices.size()];
//    std::copy(this->vertices.begin(), this->vertices.end(), vertArray);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), vertArray, GL_STATIC_DRAW);
//
//    // Create Element Buffer Object
//    // glGenBuffers(1, &EBO);
//    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->numInds, this->indices, GL_STATIC_DRAW);
//
//    // Set up vertex attributes for shader input
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
//    // glEnableVertexAttribArray(1);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    glBindVertexArray(0);
//}

void ModelComponent::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos)
{
    Transform transform = parent->getWorldTransform();
    this->shader.use();

//    glBindVertexArray(this->VAO);
//
//    shader.setInt("material.diffuse", 0);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, this->diffuseTexture);
//
//    shader.setInt("material.specular", 1);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, this->specularTexture);


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
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glBindVertexArray(0);
    model.draw(shader);
}