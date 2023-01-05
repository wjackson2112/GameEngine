//
// Created by Will on 6/8/2022.
//

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>
#include <glm/glm.hpp>

class Texture2D
{
public:
    unsigned int id;
    unsigned int width, height;
    unsigned int internalFormat, imageFormat;
    unsigned int wrapS, wrapT;
    unsigned int minFilter, maxFilter;

    Texture2D();

    virtual void generate(unsigned int width, unsigned int height, unsigned char* data);
    void bind() const;
};

#endif //TEXTURE2D_H
