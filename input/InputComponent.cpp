#include "InputComponent.h"

#include "InputManager.h"

InputComponent::InputComponent(std::vector<Key> keys)
{
    // Register base inputs
	flags = keys;
	InputManager::getInstance()->registerReceiver(this, flags);
}