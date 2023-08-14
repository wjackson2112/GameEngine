//
// Created by Will on 10/2/2022.
//

#include "TextFont.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

void TextFont::load(const char* path, int size)
{
    FT_Library ft;
    FT_Face face;

    if(FT_Init_FreeType(&ft))
        std::cout << "ERROR:FREETYPE: Could not init FreeType Library" << std::endl;

    if(FT_New_Face(ft, path, 0, &face))
        std::cout << "ERROR:FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    maxBearingY = 0;
    for(unsigned char c = 0; c < 128; c++)
    {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR:FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }

        Texture2D texture;
        texture.internalFormat = GL_RED;
        texture.imageFormat = GL_RED;
        texture.wrapS = GL_CLAMP_TO_EDGE;
        texture.wrapT = GL_CLAMP_TO_EDGE;

        texture.generate(face->glyph->bitmap.width,
                         face->glyph->bitmap.rows,
                         face->glyph->bitmap.buffer);

        TextCharacter textCharacter = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
        };

        textCharacters.insert(std::pair<char, TextCharacter>(c, textCharacter));

        // Record the tallest overall bearing to use as the height offset for top-left text alignment
        maxBearingY = textCharacter.bearing.y > maxBearingY ? textCharacter.bearing.y : maxBearingY;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

TextFont::TextCharacter TextFont::getCharacter(char rawChar)
{
    return textCharacters[rawChar];
}