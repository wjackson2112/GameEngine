//
// Created by Will on 1/6/2023.
//

#ifndef SPRITE_SHEET_COMPONENT_2D_H
#define SPRITE_SHEET_COMPONENT_2D_H

#include "SpriteComponent2D.h"
#include "Texture2D.h"

class SpriteSheetComponent2D : public SpriteComponent2D
{
    unsigned int sheetFBO = 0;
    unsigned int spriteFBO = 0;
    Texture2D textureSheet;
    glm::vec2 gridSize;

public:
    SpriteSheetComponent2D(Shader shader, Texture2D textureSheet, glm::vec2 size, glm::vec2 gridSize,
                           glm::vec2 initialCoordinate = glm::vec2(0, 0));

    void setSprite(glm::vec2 spriteCoordinate);
};

#endif //SPRITE_SHEET_COMPONENT_2D_H
