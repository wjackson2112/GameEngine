//
// Created by Will on 9/14/2022.
//

#ifndef AUDIO_CONTEXT_COMPONENT_H
#define AUDIO_CONTEXT_COMPONENT_H

#include "Component.h"

#include <openal-soft-1.22.2/include/AL/alc.h>

class AudioContextComponent : public Component
{
    ALCdevice *device;
    ALCcontext* openALContext;
public:
    AudioContextComponent();
    ~AudioContextComponent();
};

#endif //AUDIO_CONTEXT_COMPONENT_H
