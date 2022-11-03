#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>
#include <vector>
#include <GLFW\glfw3.h>
#include "Keys.h"
#include "IInputReceiver.h"

class InputManager
{
	static InputManager* instance;
	std::map<IInputReceiver*, std::vector<Key>> receivers;

	// This is a singleton so the constructor is private
	InputManager() = default;

public:

	static InputManager *getInstance();

	void registerReceiver(IInputReceiver* receiver, std::vector<Key> flags);

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
