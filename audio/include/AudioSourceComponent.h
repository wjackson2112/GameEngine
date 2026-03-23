//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 9/9/2022.
//

#ifndef AUDIO_SOURCE_COMPONENT_H
#define AUDIO_SOURCE_COMPONENT_H

#include <string>
#include <map>

#include "Component.h"
#include "AudioStream.h"

class AudioSourceComponent : public Component
{
private:

    ALuint source;
    std::map<std::string, AudioStream*> streams;

public:
    AudioSourceComponent();
    ~AudioSourceComponent();

    void play(AudioClip clip, std::string name, bool looping = false);
    void stop(std::string name);

    bool isPlaying();

    void update(float deltaTime) override;
};

#endif //AUDIO_SOURCE_COMPONENT_H
