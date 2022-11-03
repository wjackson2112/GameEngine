//
// Created by Will on 6/10/2022.
//
#include "SpriteComponent2D.h"

#include <glad/glad.h>
#include "Entity.h"

SpriteComponent2D::SpriteComponent2D(Shader shader, Texture2D texture, glm::vec2 size)
: shader(shader)
, texture(texture)
, size(size)
, blendFunc(GL_ONE_MINUS_SRC_ALPHA)
{
    this->InitRenderData();
    this->color = glm::vec3(1.0f);
}

SpriteComponent2D::~SpriteComponent2D()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteComponent2D::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos)
{
    glBlendFunc(GL_SRC_ALPHA, blendFunc);
    shader.use();

    // Start with the accrued transform of the parent
    Transform transform = parent->getWorldTransform();

    // Set Origin to Center
//    transform.translate(glm::vec3(-size.x/2, -size.y/2, 0.0f));

    // Scale to size
    transform.scaleTo(glm::vec3(size.x, size.y, 0.0f));

    shader.setMat4("model", transform.getModel());
    shader.setMat4("projection", projection);
    shader.setVec3("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // TODO: This should be reset to a global value set by the Window
}

void SpriteComponent2D::setColor(glm::vec3 color)
{
    this->color = color;
}

void SpriteComponent2D::setSize(glm::vec2 size)
{
    this->size = size;
}

void SpriteComponent2D::InitRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    // vertices for two triangles (1 quad)
    float vertices[] = {
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}