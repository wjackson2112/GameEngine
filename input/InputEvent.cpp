//
// Created by Will on 5/2/2024.
//

#include "InputEvent.h"
#include "InputManager.h"

InputEvent::InputEvent(Key key, Action action, Modifier mods)
        : position(glm::vec2(0,0))
        , key(key)
        , mouseButton(MOUSE_BUTTON_NONE)
        , action(action)
        , mods(mods)
        , padButton(GAMEPAD_BUTTON_NONE)
        , axis(GAMEPAD_AXIS_NONE)
        , axisValue(0.0f)
        , eventType(IET_KEY)
{
    timeSeconds = glfwGetTime();
}

InputEvent::InputEvent(glm::vec2 position, MouseButton mouseButton, Action action, Modifier mods)
                    : position(position)
                    , key(KEY_UNKNOWN)
                    , mouseButton(mouseButton)
                    , action(action)
                    , mods(mods)
                    , padButton(GAMEPAD_BUTTON_NONE)
                    , axis(GAMEPAD_AXIS_NONE)
                    , axisValue(0.0f)
                    , eventType(IET_MOUSE)
{
    timeSeconds = glfwGetTime();
}

InputEvent::InputEvent(GamepadButton padButton, GamepadAxis axis, float axisValue, Action action)
            : position(InputManager::getCursorPosition())
            , key(KEY_UNKNOWN)
            , mouseButton(MOUSE_BUTTON_NONE)
            , action(action)
            , mods(MOD_NONE)
            , padButton(padButton)
            , axis(axis)
            , axisValue(axisValue)
            , eventType(IET_GAMEPAD)
{
    timeSeconds = glfwGetTime();
}

InputEvent::InputEvent(Event event, Action action)
        : position(InputManager::getCursorPosition())
        , key(KEY_UNKNOWN)
        , mouseButton(MOUSE_BUTTON_NONE)
        , action(action)
        , mods(MOD_NONE)
        , padButton(GAMEPAD_BUTTON_NONE)
        , axis(GAMEPAD_AXIS_NONE)
        , axisValue(0.0f)
        , eventType(IET_MOUSE)
{
    timeSeconds = glfwGetTime();
}
