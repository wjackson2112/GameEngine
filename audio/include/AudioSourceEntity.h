//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 9/8/2022.
//

#ifndef AUDIO_SOURCE_ENTITY_H
#define AUDIO_SOURCE_ENTITY_H

#include <string>
#include "Entity.h"

class AudioSourceEntity : public Entity
{
public:
    AudioSourceEntity(std::string path);
};

#endif //AUDIO_SOURCE_ENTITY_H
