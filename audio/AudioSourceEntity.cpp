//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 9/8/2022.
//

#include "AudioSourceEntity.h"
#include "AssetManager.h"

#include "AudioSourceComponent.h"

AudioSourceEntity::AudioSourceEntity(std::string path) {
    auto srcComponent = new AudioSourceComponent();
    addComponent<AudioSourceComponent>(srcComponent);

    AudioClip clip = AssetManager::getInstance()->loadAudioClip(path.c_str(), AF_WAV, path);
    srcComponent->play(clip, path, true);

    shouldUpdate = true;
}