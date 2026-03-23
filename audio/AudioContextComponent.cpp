//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 9/14/2022.
//

#include "AudioContextComponent.h"

#include <iostream>
#include "al_error.h"

AudioContextComponent::AudioContextComponent()
{
    device = alcOpenDevice(nullptr);
    if (!device)
        std::cout << "Device failed" << std::endl;

    openALContext = alcCreateContext(device, nullptr); al_error::alcCheckError(device);
    if (!openALContext)
        std::cout << "Context failed" << std::endl;

    ALCboolean contextMadeCurrent = false;
    contextMadeCurrent = alcMakeContextCurrent(openALContext); al_error::alcCheckError(device);
    if(!contextMadeCurrent)
        std::cout << "Make Current failed" << std::endl;
}

AudioContextComponent::~AudioContextComponent()
{
    alcDestroyContext(openALContext); al_error::alcCheckError(device);
    alcCloseDevice(device); al_error::alcCheckError(device);
}