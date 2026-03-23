//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 9/8/2022.
//

#ifndef AUDIOCLIP_H
#define AUDIOCLIP_H

#include <openal-soft-1.22.2/include/AL/al.h>
#include <stdint.h>
#include <vector>
#include <string>

enum AudioFileFormat
{
    AF_WAV
};

class AudioClip
{
private:
    uint8_t channels;
    int32_t sampleRate;
    uint8_t bitsPerSample;
    std::vector<char> soundData;

    ALenum format;
public:
    void load(std::string path, AudioFileFormat fileFormat);

    int32_t getSampleRate() { return sampleRate; }
    ALenum getFormat() { return format; }
    std::vector<char> getSoundData() { return soundData; }
};

#endif //AUDIOCLIP_H
