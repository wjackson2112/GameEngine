//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 8/9/2022.
//

#ifndef TEXTURE2DMS_H
#define TEXTURE2DMS_H

#include "Texture2D.h"

class Texture2DMS : public Texture2D
{
    unsigned int numSamples;

public:
    explicit Texture2DMS(unsigned int numSamples) : Texture2D(), numSamples(numSamples) {};

    void generate(unsigned int width, unsigned int height, unsigned char* data) override;
};

#endif //TEXTURE2DMS_H
