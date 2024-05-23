//
// Created by Will on 7/20/2022.
//

#include <algorithm>
#include "EventManager.h"

EventManager* EventManager::getInstance()
{
    if(!instance)
        instance = new EventManager();
    return instance;
}
void EventManager::registerReceiver(IEventReceiver* receiver)
{
    this->receivers.push_back(receiver);
}

void EventManager::broadcastEvent(Event event) {
    EventManager* manager = getInstance();

    for(auto const& receiver : manager->receivers)
    {
        receiver->eventCallback(event);
    }
}

void EventManager::deregisterReceiver(IEventReceiver *receiver) {
    EventManager* manager = getInstance();

    manager->receivers.erase(std::remove(manager->receivers.begin(), manager->receivers.end(), receiver), manager->receivers.end());
}

EventManager *EventManager::instance = 0;