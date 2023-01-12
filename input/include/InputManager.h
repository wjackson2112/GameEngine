#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>
#include <vector>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include "Inputs.h"
#include "IInputReceiver.h"

struct InputConfig
{
    std::vector<Key> keys = std::vector<Key>();
    std::vector<MouseButton> mouseButtons = std::vector<MouseButton>();
    bool receivesMousePosition = false;
};

class InputManager
{

	static InputManager* instance;
	std::map<IInputReceiver*, InputConfig> receivers;

    glm::vec2 cursorPos = glm::vec2(0, 0);
    std::vector<Action> mouseState = std::vector<Action>(MOUSE_BUTTON_LAST, ACTION_NONE);

	// This is a singleton so the constructor is private
	InputManager() = default;

public:

	static InputManager *getInstance();

	void registerReceiver(IInputReceiver* receiver, InputConfig config);
    void deregisterReceiver(IInputReceiver* receiver);

    bool getLastMouseState(MouseButton button) { return mouseState[button]; }

	static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
