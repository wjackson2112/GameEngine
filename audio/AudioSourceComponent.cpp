//
// Created by Will on 9/12/2022.
//
#include "AudioSourceComponent.h"

#include <openal-soft-1.22.2/include/AL/al.h>
#include <algorithm>

#include "AudioStream.h"
#include "al_error.h"


AudioSourceComponent::AudioSourceComponent()
{
    shouldUpdate = true;
//    alGenSources(1, &source); al_error::alCheckError();
//    alSourcef(source, AL_PITCH, 1); al_error::alCheckError();
//    alSourcef(source, AL_GAIN, 1.0f); al_error::alCheckError();
//    alSource3f(source, AL_POSITION, 0, 0, 0); al_error::alCheckError();
//    alSource3f(source, AL_VELOCITY, 0, 0, 0); al_error::alCheckError();
//    alSourcei(source, AL_LOOPING, AL_FALSE); al_error::alCheckError();
}

AudioSourceComponent::~AudioSourceComponent()
{
    streams.clear();
//    alDeleteSources(1, &source); al_error::alCheckError();
}

void AudioSourceComponent::play(AudioClip clip, std::string name, bool looping /* = false */)
{
    AudioStream* stream = new AudioStream(clip);
    stream->play(looping);
    streams[name] = stream;
}

void AudioSourceComponent::stop(std::string name)
{

}

void AudioSourceComponent::update(float deltaTime)
{
    for(auto it = streams.begin(); it != streams.end();)
    {
        AudioStream* stream = it->second;
        stream->update();
        if(stream->state == AL_STOPPED)
            streams.erase(it++);
        else
            ++it;
    }
}

bool AudioSourceComponent::isPlaying()
{
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state); al_error::alCheckError();
    return state == AL_PLAYING;
}
