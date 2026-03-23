//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 9/8/2022.
//

#ifndef WAV_H
#define WAV_H

#include <cstring>
#include <fstream>
#include <vector>
#include <cstdint>

#include <openal-soft-1.22.2/include/AL/al.h>
#include <openal-soft-1.22.2/include/AL/alc.h>

namespace wav
{
    bool isBigEndian();

    std::int32_t charArrayToInt(char* buffer, std::size_t len);

    bool loadHeader(std::ifstream& file,
                    std::uint8_t& channels,
                    std::int32_t& sampleRate,
                    std::uint8_t& bitsPerSample,
                    ALsizei& size);

    bool load(const std::string& filename,
              std::uint8_t& channels,
              std::int32_t& sampleRate,
              std::uint8_t& bitsPerSample,
              std::vector<char>& soundData);
}

#endif //WAV_H
