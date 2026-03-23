//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 9/12/2022.
//

#include "AudioStream.h"

#include <iostream>
#include <algorithm>
#include <cstring>

#include <al_error.h>

const std::size_t BUFFER_SIZE = 65536;

AudioStream::AudioStream(AudioClip clip)
: clip(clip)
, cursor(0)
{
    alGenSources(1, &source); al_error::alCheckError();
    alSourcef(source, AL_PITCH, 1); al_error::alCheckError();
    alSourcef(source, AL_GAIN, 1.0f); al_error::alCheckError();
    alSource3f(source, AL_POSITION, 0, 0, 0); al_error::alCheckError();
    alSource3f(source, AL_VELOCITY, 0, 0, 0); al_error::alCheckError();
    alSourcei(source, AL_LOOPING, AL_FALSE); al_error::alCheckError();

    numBuffers = std::max(1, (int) std::min(clip.getSoundData().size() / BUFFER_SIZE, MAX_NUM_BUFFERS));

    alGenBuffers(numBuffers, &buffers[0]); al_error::alCheckError();

    if(numBuffers == 1 && clip.getSoundData().size() < BUFFER_SIZE)
    {
        alBufferData(buffers[0],
                     clip.getFormat(),
                     &clip.getSoundData()[0],
                     clip.getSoundData().size(),
                     clip.getSampleRate());
        al_error::alCheckError();
    }
    else
    {
        for(std::size_t i = 0; i < numBuffers; ++i)
        {
            alBufferData(buffers[i],
                         clip.getFormat(),
                         &clip.getSoundData()[i * BUFFER_SIZE],
                         BUFFER_SIZE, clip.getSampleRate());
            al_error::alCheckError();
        }
    }
}

AudioStream::~AudioStream()
{
    alDeleteBuffers(numBuffers, &buffers[0]); al_error::alCheckError();
    alDeleteSources(1, &source); al_error::alCheckError();
}

void AudioStream::play(bool in_looping /* = false */)
{
    looping = in_looping;

    alSourceQueueBuffers(source, numBuffers, &buffers[0]); al_error::alCheckError();
    alSourcePlay(source); al_error::alCheckError();

    cursor = BUFFER_SIZE * numBuffers;
    state = AL_PLAYING;
}

void AudioStream::update()
{
    ALint buffersProcessed = 0;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &buffersProcessed); al_error::alCheckError();

    if(buffersProcessed <= 0)
        return;

    while(buffersProcessed--)
    {
        ALuint buffer;
        alSourceUnqueueBuffers(source, 1, &buffer);

        ALsizei dataSize = BUFFER_SIZE;

        char* data = new char[dataSize];
        std::memset(data, 0, dataSize);

        std::size_t dataSizeToCopy = BUFFER_SIZE;

        if(!looping && cursor >= clip.getSoundData().size()) // Early out if not looping and we've reached the end
        {
            state = AL_STOPPED;
            return;
        }

        if(cursor + BUFFER_SIZE > clip.getSoundData().size())
            dataSizeToCopy = clip.getSoundData().size() - cursor; // Handle the case where there's not enough left to fill a buffer

        std::memcpy(&data[0], &clip.getSoundData()[cursor], dataSizeToCopy);
        cursor += dataSizeToCopy;

        ALuint bufferSize = BUFFER_SIZE;

        // Feed the beginning of the file into the end of the incomplete final buffer to create seamless looping
        if(dataSizeToCopy < BUFFER_SIZE)
        {
            if(looping)
            {
                cursor = 0;
                std::memcpy(&data[dataSizeToCopy], &clip.getSoundData()[cursor], BUFFER_SIZE - dataSizeToCopy);
                cursor = BUFFER_SIZE - dataSizeToCopy;
            }
            else
            {
                alGenBuffers(1, &buffer); al_error::alCheckError();
                bufferSize = dataSizeToCopy;
            }
        }

        alBufferData(buffer, clip.getFormat(), data, bufferSize, clip.getSampleRate()); al_error::alCheckError();
        alSourceQueueBuffers(source, 1, &buffer); al_error::alCheckError();

        delete[] data;
    }
}