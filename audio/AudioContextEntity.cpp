//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 9/15/2022.
//

#include "AudioContextEntity.h"

#include "AudioContextComponent.h"

AudioContextEntity::AudioContextEntity()
{
    addComponent<AudioContextComponent>(new AudioContextComponent());
}