//
// Created by Will on 9/15/2022.
//

#include "AudioContextEntity.h"

#include "AudioContextComponent.h"

AudioContextEntity::AudioContextEntity()
{
    AudioContextComponent* conComp = new AudioContextComponent();
    addComponent(conComp);
}