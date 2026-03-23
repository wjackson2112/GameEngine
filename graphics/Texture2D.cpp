//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 6/8/2022.
//
#include "Texture2D.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

Texture2D::Texture2D()
: width(0)
, height(0)
, internalFormat(GL_RGB)
, imageFormat(GL_RGB)
, wrapS(GL_REPEAT)
, wrapT(GL_REPEAT)
, minFilter(GL_LINEAR)
, maxFilter(GL_LINEAR)
{
    glGenTextures(1, &id);
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width = width;
    this->height = height;

    // create Texture
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}