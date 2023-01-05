//
// Created by Will on 9/13/2022.
//

#include "al_error.h"
#include <iostream>

void al_error::alCheckError()
{
    ALenum alError = alGetError();
    if(alError != AL_NO_ERROR)
        std::cout << "ERROR DETECTED" << std::endl;
}

void al_error::alcCheckError(ALCdevice *device)
{
    ALenum alError = alcGetError(device);
    if(alError != ALC_NO_ERROR)
        std::cout << "ERROR DETECTED" << std::endl;
}