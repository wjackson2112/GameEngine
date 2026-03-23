//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 1/6/2023.
//

#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#include "SpriteSheetComponent2D.h"

SpriteSheetComponent2D::SpriteSheetComponent2D(Shader shader, Texture2D textureSheet, glm::vec2 size, glm::vec2 gridSize,
                                               glm::vec2 initialCoordinate/* = glm::vec2(0,0)*/)
: SpriteComponent2D(shader, textureSheet, size)
, textureSheet(textureSheet)
, gridSize(gridSize)
{
    setSprite(initialCoordinate);
}

void SpriteSheetComponent2D::setSprite(glm::vec2 spriteCoordinate)
{
    // Reset to 0,0 if the grid size is too large
    if(spriteCoordinate.x >= gridSize.x || spriteCoordinate.y >= gridSize.y)
    {
        std::cout << "ERROR::SPRITESHEET:: Sprite coordinate is larger than selected grid size" << std::endl;
        spriteCoordinate.x = 0;
        spriteCoordinate.y = 0;
    }

    texture = Texture2D();
    texture.width = textureSheet.width / gridSize.x;
    texture.height = textureSheet.height / gridSize.y;
    texture.generate(texture.width, texture.height, nullptr);

    // Configure Sheet Framebuffer
    glGenFramebuffers(1, &sheetFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, sheetFBO);

    // Create Sheet Color Attachment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureSheet.id, 0);

    // Check for completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Sheet framebuffer is not complete!" << std::endl;

    // Configure Sprite Framebuffer
    glGenFramebuffers(1, &spriteFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, spriteFBO);

    // Create Sprite Color Attachment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);

    // Check for completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Sprite framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_READ_FRAMEBUFFER, sheetFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, spriteFBO);
    glBlitFramebuffer(texture.width * spriteCoordinate.x + 1, texture.height * (gridSize.y - spriteCoordinate.y),
                      texture.width * (spriteCoordinate.x + 1) + 1, texture.height * (gridSize.y - spriteCoordinate.y - 1),
                      0, texture.height,
                      texture.width, 0,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}