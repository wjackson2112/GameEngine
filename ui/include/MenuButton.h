//
// Created by Will on 12/8/2022.
//

#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "Entity.h"
#include "IInputReceiver.h"
#include "IEventReceiver.h"

class MenuButton : public Entity, IInputReceiver
{
    glm::vec2 size;
    Event event;

public:
    MenuButton(glm::vec2 origin, glm::vec2 size, std::string background, std::string text, Event event);
    ~MenuButton();

    //IInputReceiver
    void mouseInputCallback(double xpos, double ypos, MouseButton button, Action action, Modifier mods) override;
    void keyInputCallback(Key key, int scancode, Action action, Modifier mods) override {};
};

#endif //MENU_BUTTON_H
