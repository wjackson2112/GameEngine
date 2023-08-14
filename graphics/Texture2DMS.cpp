//
// Created by Will on 8/9/2022.
//

#include "Texture2DMS.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

void Texture2DMS::generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width = width;
    this->height = height;

    // create Texture
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, id);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, numSamples, internalFormat, width, height, GL_TRUE);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, wrapT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, maxFilter);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
}