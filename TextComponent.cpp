//
// Created by Will on 10/2/2022.
//

#include <iostream>
#include <glad/glad.h>
#include "TextComponent.h"
#include "AssetManager.h"
#include "Entity.h"


TextComponent::TextComponent(Shader shader, TextFont textFont, std::string text)
: shader(shader)
, textFont(textFont)
, text(text)
, rows(12)
, color(glm::vec3(1.0f))
, blendFunc(GL_ONE_MINUS_SRC_ALPHA)
{
    this->InitRenderData();
}

void TextComponent::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos)
{
    glBlendFunc(GL_SRC_ALPHA, blendFunc);
    shader.use();

    // Start with the accrued transform of the parent
    Transform transform = parent->getWorldTransform();

    for(int i = 0; i < text.size(); i++)
    {
        char currentChar = text[i];
        TextFont::TextCharacter textChar = textFont.getCharacter(currentChar);
        unsigned int advance = textChar.advance/64;

        // Set Origin to Bottom-Left
        transform.translate(glm::vec3(0.0f, -textChar.size.y, 0.0f));

        transform.translate(glm::vec3(textChar.bearing.x, textChar.size.y - textChar.bearing.y, 0.0f));

        // Scale to the actual size
        transform.scaleTo(glm::vec3(textChar.size.x,
                                    textChar.size.y,
                                    1.0f));

        shader.setMat4("model", transform.getModel());
        shader.setMat4("projection", projection);
        shader.setVec3("spriteColor", color);

        glActiveTexture(GL_TEXTURE0);
        textChar.texture.bind();

        glBindVertexArray(this->quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // TODO: This should be reset to a global value set by the Window

        // Undo scale before translating
        transform.scaleTo(glm::vec3(1.0f, 1.0f, 1.0f));

        // Undo height offset
        transform.translate(glm::vec3(0.0f, textChar.size.y, 0.0f));

        transform.translate(glm::vec3(-textChar.bearing.x, -(textChar.size.y - textChar.bearing.y), 0.0f));

        // Advance and set height
        transform.translate(glm::vec3((float) advance, 0, 0));
    }
}

void TextComponent::setColor(glm::vec3 color)
{
    this->color = color;
}

//void TextComponent::loadCharacters()
//{
//    loaded_characters = true;
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//    for(unsigned char c = 0; c < 128; c++)
//    {
//        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
//        {
//            std::cout << "ERROR:FREETYPE: Failed to load Glyph" << std::endl;
//            continue;
//        }
//
//        Texture2D texture;
//        texture.internalFormat = GL_RED;
//        texture.imageFormat = GL_RED;
//        texture.wrapS = GL_CLAMP_TO_EDGE;
//        texture.wrapT = GL_CLAMP_TO_EDGE;
//
//        texture.generate(face->glyph->bitmap.width,
//                         face->glyph->bitmap.rows,
//                         face->glyph->bitmap.buffer);
//
//        Character character = {
//                texture,
//                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//                static_cast<unsigned int>(face->glyph->advance.x)
//        };
//
//        characters.insert(std::pair<char, Character>(c, character));
//    }
//}

//TextComponent::~TextComponent()
//{
//    FT_Done_Face(face);
//    FT_Done_FreeType(ft);
//}

void TextComponent::InitRenderData()
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