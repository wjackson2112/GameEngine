//
// Created by Will on 9/12/2022.
//

#ifndef AUDIO_STREAM_H
#define AUDIO_STREAM_H

#include "AudioClip.h"

#include <openal-soft-1.22.2/include/AL/al.h>
#include <openal-soft-1.22.2/include/AL/alc.h>

const std::size_t MAX_NUM_BUFFERS = 4;

struct AudioStream
{
    AudioClip clip;
    std::size_t cursor;
    ALuint buffers[MAX_NUM_BUFFERS];
    ALuint numBuffers;
    ALint state;
    ALuint source;
    bool looping;

    AudioStream(AudioStream&&)=default;
    AudioStream& operator=(AudioStream&&)=default;

    explicit AudioStream(AudioClip clip);
    ~AudioStream();

    void play(bool looping = false);
    void update();
};

#endif //AUDIO_STREAM_H
