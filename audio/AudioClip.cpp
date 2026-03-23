//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 9/9/2022.
//

#include "AudioClip.h"

#include <iostream>
#include "wav.h"

void AudioClip::load(std::string path, AudioFileFormat fileFormat)
{
    if(fileFormat == AF_WAV)
    {
        if(!wav::load(path, channels, sampleRate, bitsPerSample, soundData))
        {
            std::cerr << "ERROR: Could not load wav" << std::endl;
            return;
        }

        if(channels == 1 && bitsPerSample == 8)
            format = AL_FORMAT_MONO8;
        else if(channels == 1 && bitsPerSample == 16)
            format = AL_FORMAT_MONO16;
        else if(channels == 2 && bitsPerSample == 8)
            format = AL_FORMAT_STEREO8;
        else if(channels == 2 && bitsPerSample == 16)
            format = AL_FORMAT_STEREO16;
        else
        {
            std::cerr
                    << "ERROR: unrecognized wave format: "
                    << channels << " channels, "
                    << bitsPerSample << " bps" << std::endl;
            return;
        }
    }
}