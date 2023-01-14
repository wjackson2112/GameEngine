//
// Created by Will on 10/2/2022.
//

#ifndef TEXT_FONT_H
#define TEXT_FONT_H

#include <map>
#include "Texture2D.h"

class TextFont
{
public:
    struct TextCharacter
    {
        Texture2D texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        unsigned int advance;
    };

    int maxBearingY;

    void load(const char* path, int size);

    TextCharacter getCharacter(char rawChar);
private:
    std::map<char, TextCharacter> textCharacters;
};

#endif //TEXT_FONT_H
