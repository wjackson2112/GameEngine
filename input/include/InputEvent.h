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

    Action action;
    Modifier mods;

    InputEvent() = default;

    InputEvent(Key key, Action action, Modifier mods);
    InputEvent(glm::vec2 position, MouseButton mouseButton, Action action, Modifier mods);
    InputEvent(GamepadButton padButton, GamepadAxis axis, float axisValue, Action action);
    InputEvent(Event event, Action action);

    inline bool isKeyEvent() { return eventType == IET_KEY; }
    inline bool isMouseEvent() { return eventType == IET_MOUSE; }
    inline bool isGamepadEvent() { return eventType == IET_GAMEPAD; }
};

#endif //INPUT_EVENT_H
