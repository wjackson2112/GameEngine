#include "InputComponent.h"

#include "InputManager.h"
#include "Entity.h"

#include <algorithm>

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

void InputComponent::lateUpdate(float deltaTime)
{
    while(!inputEvents.empty())
        inputEvents.pop();
}

void InputComponent::mouseInputCallback(double xpos, double ypos, MouseButton button, Action action, Modifier mods)
{
    // Don't listen for input if the parent isn't receiving updates
    if(getParent()->receivesUpdates)
        inputEvents.push(InputEvent(glm::vec2(xpos, ypos), button, action, mods));
}

void InputComponent::keyInputCallback(Key key, int scancode, Action action, Modifier mods)
{
    // Don't listen for input if the parent isn't receiving updates
    if(getParent()->receivesUpdates)
        inputEvents.push(InputEvent(key, action, mods));
}