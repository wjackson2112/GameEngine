//
// Created by Will on 12/12/2022.
//

#include "OptionsManager.h"

OptionsManager *OptionsManager::instance = nullptr;

OptionsManager::OptionsManager()
: windowSize(glm::vec2(1600.0f,1200.0f))
, viewportResolution(glm::vec2(1600.0f,1200.0f))
{}

OptionsManager *OptionsManager::getInstance()
{
    if(!instance)
        instance = new OptionsManager();
    return instance;
}

void OptionsManager::deregisterReceiver(IOptionsReceiver *receiver)
{
    for(auto it = receivers.begin(); it != receivers.end(); it++)
    {
        if (*it == receiver) {
            receivers.erase(it);
            break;
        }
    }
}