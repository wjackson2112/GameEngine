//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 12/8/2022.
//

#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "Entity.h"
#include "IEventReceiver.h"

class MenuButton : public Entity, IEventReceiver
{
    glm::vec2 size;
    Event boundEvent;

public:
    MenuButton(glm::vec2 origin, glm::vec2 size, std::string background, std::string text, Event event);

    void eventCallback(Event event) override;
};

#endif //MENU_BUTTON_H
