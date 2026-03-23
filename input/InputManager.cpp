
//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

#include "InputManager.h"
#include "OptionsManager.h"
#ifdef __EMSCRIPTEN__
#include "emscripten/key_codes.h"
#endif

InputManager* InputManager::getInstance()
{
	if(!instance)
		instance = new InputManager();
	return instance;
}

void InputManager::addBinding(MouseButton button, ButtonAction action, Event event, int mods /*= 0*/) {
    bindings.emplace_back(button, action, event, mods);
}

void InputManager::addBinding(Key button, ButtonAction action, Event event, int mods /*= 0*/) {
    bindings.emplace_back(button, action, event, mods);
}

void InputManager::addBinding(GamepadButton button, ButtonAction action, Event event) {
    bindings.emplace_back(button, action, event);
}

void InputManager::addBinding(GamepadAxis axis, ButtonAction action, Event event) {
    bindings.emplace_back(axis, action, event);
}

void InputManager::clearBindings() {
    bindings.clear();
}

void InputManager::setCursorPosition(double xpos, double ypos)
{
    InputManager* manager = getInstance();

    manager->cursorPos = glm::vec2(xpos, ypos);
}

void InputManager::setCursorPosition(glm::vec2 position)
{
    setCursorPosition(position.x, position.y);
}

void InputManager::mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager* manager = getInstance();

    if(manager->inputMode != IM_MKB)
    {
        manager->inputMode = IM_MKB;
        EventManager::getInstance()->broadcastEvent(Event(Event::EVT_SWITCH_INPUT_MODE));
    }

    // Convert screen mouse coordinate to viewport mouse coordinate
    glm::vec2 windowSize = OptionsManager::getInstance()->getWindowSize();
    glm::vec2 viewportRes = OptionsManager::getInstance()->getViewportResolution();

    manager->cursorPos = glm::vec2(xpos, ypos);

    for(ActionBinding binding : manager->bindings)
    {
        // Drag event
        if (binding.button == (MouseButton) manager->lastMouseButton &&
            binding.action == (ButtonAction) BUTTON_ACTION_DRAG &&
            manager->lastMouseAction == BUTTON_ACTION_PRESS) {
            EventManager::getInstance()->broadcastEvent(binding.event);
        }
            // Generic movement
        else if (binding.button == (MouseButton) MOUSE_BUTTON_NONE &&
                 binding.action == (ButtonAction) BUTTON_ACTION_NONE) {
            EventManager::getInstance()->broadcastEvent(binding.event);
        }
    }
}

void InputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    InputManager* manager = getInstance();

    if(manager->inputMode != IM_MKB)
    {
        manager->inputMode = IM_MKB;
        EventManager::getInstance()->broadcastEvent(Event(Event::EVT_SWITCH_INPUT_MODE));
    }

    manager->mouseState[button] = (ButtonAction) action;

    manager->lastMouseButton = (MouseButton) button;
    manager->lastMouseAction = (ButtonAction) action;

    for(ActionBinding binding : manager->bindings)
    {
        if (!binding.isMouseBind())
            continue;
        if (binding.button == button && binding.action == action)
            EventManager::getInstance()->broadcastEvent(binding.event);
    }
}

void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager* manager = getInstance();

    if(manager->inputMode != IM_MKB)
    {
        manager->inputMode = IM_MKB;
        EventManager::getInstance()->broadcastEvent(Event(Event::EVT_SWITCH_INPUT_MODE));
    }

    for(ActionBinding binding : manager->bindings)
    {
        if (!binding.isKeyBind())
            continue;
        if (binding.key == key && binding.action == action && (binding.mods & mods) == binding.mods)
            EventManager::getInstance()->broadcastEvent(binding.event);
    }
}

#ifdef __EMSCRIPTEN__
EM_BOOL InputManager::em_keydown(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
    return EM_TRUE;
}
#endif

void InputManager::pollGamepad()
{
#ifndef __EMSCRIPTEN__
    static GamepadHandle gamepadHandle = GAMEPAD_HANDLE_NONE;
    InputManager* manager = getInstance();

    // TODO: Make this a stand alone function to get the gamepad handle
    if(gamepadHandle == GAMEPAD_HANDLE_NONE || !glfwJoystickIsGamepad(gamepadHandle))
        for(int i = 0; i < GAMEPAD_HANDLE_MAX; i++)
            if(glfwJoystickPresent(i) && glfwJoystickIsGamepad(i))
                gamepadHandle = (GamepadHandle) i;

    // If still no gamepad detected, get out
    if(gamepadHandle == GAMEPAD_HANDLE_NONE || !glfwJoystickIsGamepad(gamepadHandle))
        return;


    if(glfwGetGamepadState(gamepadHandle, &currState))
    {
        for(int i = 0; i < GAMEPAD_BUTTON_MAX; i++)
        {
            // If the state hasn't changed, continue
            if (currState.buttons[i] == prevState.buttons[i])
                continue;

            if(manager->inputMode != IM_GAMEPAD)
            {
                manager->inputMode = IM_GAMEPAD;
                EventManager::getInstance()->broadcastEvent(Event(Event::EVT_SWITCH_INPUT_MODE));
            }

            GamepadButton gamepadButton = (GamepadButton) i;
            ButtonAction action = (ButtonAction) currState.buttons[i];

            for (ActionBinding binding: bindings) {
                if (!binding.isGamepadButtonBind())
                    continue;
                if (binding.gamepadButton == gamepadButton && binding.action == action)
                    EventManager::getInstance()->broadcastEvent(binding.event);
            }
        }

        for(int i = 0; i < GAMEPAD_AXIS_MAX; i++)
        {
            if(currState.axes[i] == prevState.axes[i])
                continue;

            if(manager->inputMode != IM_GAMEPAD)
            {
                manager->inputMode = IM_GAMEPAD;
                EventManager::getInstance()->broadcastEvent(Event(Event::EVT_SWITCH_INPUT_MODE));
            }

            GamepadAxis gamepadAxis = (GamepadAxis) i;
            ButtonAction action = (ButtonAction) currState.axes[i];

            for (ActionBinding binding: bindings) {
                if (!binding.isGamepadAxisBind())
                    continue;
                if (binding.gamepadAxis == gamepadAxis && binding.action == action)
                    EventManager::getInstance()->broadcastEvent(binding.event);
            }
        }
    }
#endif
    prevState = currState;
}

InputManager *InputManager::instance = 0;
