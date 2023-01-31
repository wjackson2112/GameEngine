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

KeyEvent InputComponent::dequeueKeyEvent()
{
    if(keyEvents.empty())
        return {};

    KeyEvent next = keyEvents.front();
    keyEvents.pop();
    return next;
}

MouseEvent InputComponent::dequeueMouseEvent()
{
    if(mouseEvents.empty())
        return {};

    MouseEvent next = mouseEvents.front();
    mouseEvents.pop();
    return next;
}

void InputComponent::lateUpdate(float deltaTime)
{
    while(!keyEvents.empty())
        keyEvents.pop();

    while(!mouseEvents.empty())
        mouseEvents.pop();
}

void InputComponent::mouseInputCallback(double xpos, double ypos, MouseButton button, Action action, Modifier mods)
{
    // Don't listen for input if the parent isn't receiving updates
    if(getParent()->receivesUpdates)
        mouseEvents.push(MouseEvent(glm::vec2(xpos, ypos), button, action, mods));
}

void InputComponent::keyInputCallback(Key key, int scancode, Action action, Modifier mods)
{
    // Don't listen for input if the parent isn't receiving updates
    if(getParent()->receivesUpdates)
        keyEvents.push(KeyEvent(key, action, mods));
}