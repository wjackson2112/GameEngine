//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 9/13/2022.
//

#ifndef AL_ERROR_CHECK_H
#define AL_ERROR_CHECK_H

#include <openal-soft-1.22.2/include/AL/al.h>
#include <openal-soft-1.22.2/include/AL/alc.h>

namespace al_error {
    void alCheckError();
    void alcCheckError(ALCdevice *device);
}

#endif //AL_ERROR_CHECK_H
