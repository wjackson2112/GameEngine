//
// Created by Will on 12/12/2022.
//

#include "OptionsManager.h"

OptionsManager *OptionsManager::instance = nullptr;

OptionsManager::OptionsManager()
: screenResolution(glm::vec2(1600.0f,1200.0f))
, viewportResolution(glm::vec2(800.0f,600.0f))
{}

OptionsManager *OptionsManager::getInstance()
{
    if(!instance)
        instance = new OptionsManager();
    return instance;
}