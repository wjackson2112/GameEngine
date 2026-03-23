//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 7/20/2022.
//

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <vector>

#include "IEventReceiver.h"

class EventManager
{
    static EventManager* instance;
    std::vector<IEventReceiver*> receivers;

    // This is a singleton so the constructor is private
    EventManager() = default;

public:
    static EventManager *getInstance();

    void registerReceiver(IEventReceiver* receiver);
    void deregisterReceiver(IEventReceiver* receiver);

    void broadcastEvent(Event event);
};

#endif //EVENT_MANAGER_H
