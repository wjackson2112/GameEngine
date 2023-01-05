
#include "InputManager.h"
#include "OptionsManager.h"

#include <algorithm>
#include <iostream>

InputManager* InputManager::getInstance()
{
	if(!instance)
		instance = new InputManager();
	return instance;
}

void InputManager::registerReceiver(IInputReceiver* receiver, std::vector<Key> flags)
{
 	this->receivers[receiver] = flags;
}

void InputManager::deregisterReceiver(IInputReceiver *receiver)
{
    for(auto it = receivers.begin(); it != receivers.end(); it++)
    {
        if (it->first == receiver) {
            receivers.erase(it);
            break;
        }
    }
}

void InputManager::mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager* manager = getInstance();

    // Convert screen mouse coordinate to viewport mouse coordinate
    glm::vec2 screenRes = OptionsManager::getInstance()->getScreenResolution();
    glm::vec2 viewportRes = OptionsManager::getInstance()->getViewportResolution();

    // TODO: This math is going to have to cover the case where there are black bars on the edge of the screen with offsets someday
    glm::vec2 ratio = screenRes/viewportRes;
    manager->cursorPos = glm::vec2(xpos/ratio.x, ypos/ratio.y);

	for(auto const& x : manager->receivers)
	{
		IInputReceiver* receiver = x.first;
		receiver->mouseInputCallback(manager->cursorPos.x, manager->cursorPos.y, MOUSE_BUTTON_NONE, ACTION_NONE, (Modifier) 0);
	}
}

void InputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    InputManager* manager = getInstance();

    for(auto const& x : manager->receivers)
    {
        IInputReceiver* receiver = x.first;
        receiver->mouseInputCallback(manager->cursorPos.x, manager->cursorPos.y, (MouseButton) button, (Action) action, (Modifier) 0);
    }
}

void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager* manager = getInstance();

	// for(auto const& [receiver, flags] : this->receivers)
	for(auto const& x : manager->receivers)
	{
		IInputReceiver* receiver = x.first;
		std::vector<Key> flags = x.second;

		if(std::find(flags.begin(), flags.end(), static_cast<Key>(key)) != flags.end())
			receiver->keyInputCallback((Key) key, scancode, (Action) action, (Modifier) mods);
	}
}

InputManager *InputManager::instance = 0;
