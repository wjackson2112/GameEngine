#include "InputComponent.h"

#include "InputManager.h"
#include "Entity.h"

#include <algorithm>
#include <iostream>

InputComponent::InputComponent(const InputConfig config)
{
    // Register base inputs
	InputManager::getInstance()->registerReceiver(this, config);

    receivesUpdates = true;
}

InputComponent::~InputComponent()
{
    InputManager::getInstance()->deregisterReceiver(this);
}

InputEvent InputComponent::dequeueEvent()
{
    if(inputEvents.empty())
        return {};

    InputEvent next = inputEvents.front();
    inputEvents.pop();
    return next;
}

void InputComponent::earlyUpdate(float deltaTime)
{
    Component::earlyUpdate(deltaTime);
#ifndef __EMSCRIPTEN__
    static GamepadHandle gamepadHandle = GAMEPAD_HANDLE_NONE;

    // TODO: Make this a stand alone function to get the gamepad handle
    if(gamepadHandle == GAMEPAD_HANDLE_NONE || !glfwJoystickIsGamepad(gamepadHandle))
        for(int i = 0; i < GAMEPAD_HANDLE_MAX; i++)
            if(glfwJoystickIsGamepad(i))
                gamepadHandle = (GamepadHandle) i;

    // If still no gamepad detected, get out
    if(gamepadHandle == GAMEPAD_HANDLE_NONE || !glfwJoystickIsGamepad(gamepadHandle))
        return;


    if(glfwGetGamepadState(gamepadHandle, &currState))
    {
        for(int i = 0; i < GAMEPAD_BUTTON_MAX; i++)
            if(currState.buttons[i] != prevState.buttons[i])
                gamepadInputCallback((GamepadButton) i, GAMEPAD_AXIS_NONE, 0.0f, (Action) currState.buttons[i]);

        for(int i = 0; i < GAMEPAD_AXIS_MAX; i++)
            if(currState.axes[i] != prevState.axes[i])
                gamepadInputCallback(GAMEPAD_BUTTON_NONE, (GamepadAxis) i, currState.axes[i], ACTION_NONE);
    }
#endif
    prevState = currState;
}

void InputComponent::lateUpdate(float deltaTime)
{
    while(!inputEvents.empty())
        inputEvents.pop();
}

void InputComponent::keyInputCallback(Key key, int scancode, Action action, Modifier mods)
{
    // Don't listen for input if the parent isn't receiving updates
    if(getParent()->receivesUpdates)
        inputEvents.push(InputEvent(key, action, mods));
}

void InputComponent::mouseInputCallback(double xpos, double ypos, MouseButton button, Action action, Modifier mods)
{
    // Don't listen for input if the parent isn't receiving updates
    if(getParent()->receivesUpdates)
        inputEvents.push(InputEvent(glm::vec2(xpos, ypos), button, action, mods));
}

void InputComponent::gamepadInputCallback(GamepadButton padButton, GamepadAxis axis, float axisValue, Action action)
{
    // Don't listen for input if the parent isn't receiving updates
    if(getParent()->receivesUpdates)
        inputEvents.push(InputEvent(padButton, axis, axisValue, action));
}
