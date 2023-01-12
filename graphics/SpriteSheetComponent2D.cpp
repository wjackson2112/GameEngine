//
// Created by Will on 1/6/2023.
//

#include <iostream>

#include <glad/glad.h>

#include "SpriteSheetComponent2D.h"

SpriteSheetComponent2D::SpriteSheetComponent2D(Shader shader, Texture2D textureSheet, glm::vec2 size, glm::vec2 gridSize,
                                               int initialX/*= 0*/, int initialY/* = 0*/)
: SpriteComponent2D(shader, textureSheet, size)
{
    // Reset to 0,0 if the grid size is too large
    if(initialX >= gridSize.x || initialY >= gridSize.y)
    {
        std::cout << "ERROR::SPRITESHEET:: Initial offset is larger than selected grid size" << std::endl;
        initialX = 0;
        initialY = 0;
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
    glBlitFramebuffer(texture.width * initialX + 1, texture.height * (gridSize.y - initialY),
                      texture.width * (initialX + 1) + 1, texture.height * (gridSize.y - initialY - 1),
                      0, 0,
                      texture.width, texture.height,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
