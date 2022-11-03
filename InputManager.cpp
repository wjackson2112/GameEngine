
#include "InputManager.h"

#include <algorithm>

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

void InputManager::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager* manager = getInstance();

	for(auto const& x : manager->receivers)
	{
		IInputReceiver* receiver = x.first;
		receiver->mouseInputCallback(xpos, ypos);
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
			receiver->keyInputCallback(key, scancode, action, mods);
	}
}

InputManager *InputManager::instance = 0;
