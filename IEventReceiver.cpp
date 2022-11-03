//
// Created by Will on 10/7/2022.
//

#include "IEventReceiver.h"
#include "EventManager.h"

IEventReceiver::IEventReceiver()
{
    EventManager::getInstance()->registerReceiver(this);
}