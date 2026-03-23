//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 5/2/2024.
//

#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

#include "EventManager.h"
#include "Inputs.h"
#include "glm/glm.hpp"

class InputManager;

enum InputEventType
{
    IET_KEY,
    IET_MOUSE,
    IET_GAMEPAD,
    IET_MAX
};

struct InputEvent
{
    double timeSeconds;

private:
    InputEventType eventType;

public:
    Key key;
    MouseButton mouseButton;
    GamepadButton padButton;
    GamepadAxis axis;
    float axisValue;
    Event event = Event(Event::EVT_NONE);

    glm::vec2 position;

    ButtonAction action;
    Modifier mods;

    InputEvent() = default;

    InputEvent(Key key, ButtonAction action, Modifier mods);
    InputEvent(glm::vec2 position, MouseButton mouseButton, ButtonAction action, Modifier mods);
    InputEvent(GamepadButton padButton, GamepadAxis axis, float axisValue, ButtonAction action);
    InputEvent(Event event, ButtonAction action);

    inline bool isKeyEvent() { return eventType == IET_KEY; }
    inline bool isMouseEvent() { return eventType == IET_MOUSE; }
    inline bool isGamepadEvent() { return eventType == IET_GAMEPAD; }
};

#endif //INPUT_EVENT_H
