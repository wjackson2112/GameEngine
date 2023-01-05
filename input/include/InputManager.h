#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>
#include <vector>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include "Inputs.h"
#include "IInputReceiver.h"

class InputManager
{
	static InputManager* instance;
	std::map<IInputReceiver*, std::vector<Key>> receivers;

    glm::vec2 cursorPos = glm::vec2(0, 0);

	// This is a singleton so the constructor is private
	InputManager() = default;

public:

	static InputManager *getInstance();

	void registerReceiver(IInputReceiver* receiver, std::vector<Key> flags);
    void deregisterReceiver(IInputReceiver* receiver);

	static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
