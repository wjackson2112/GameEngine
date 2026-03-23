//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 10/2/2022.
//

#ifndef TEXT_ENTITY_H
#define TEXT_ENTITY_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>

#include "Component.h"
#include "TextFont.h"
#include "Shader.h"

// TODO: This whole class should probably be a subclass of SpriteComponent2D
class TextComponent : public Component
{
private:

    Shader shader;
    TextFont textFont;
    std::string text;
    unsigned int rows;
    glm::vec3 color;
    int blendFunc;
    unsigned int quadVAO;

public:
    TextComponent(Shader shader, TextFont textFont, std::string text);

    inline glm::vec3 getColor() { return color; };
    void setColor(glm::vec3 color);

    inline std::string getText() { return text; };
    void setText(std::string& text);

    inline int getMaxBearingY() { return textFont.maxBearingY; };

    void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos) override;

private:
    void InitRenderData();
};

#endif //TEXT_ENTITY_H
