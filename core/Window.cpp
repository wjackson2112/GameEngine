#include "Window.h"

#include <iostream>
#include <vector>
#include "InputManager.h"
#include "OptionsManager.h"
#include "stb_image.h"

Window::Window(bool depthTest /* = true */)
: wireframeMode(false)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the GLFW Window
    glm::vec2 windowSize = OptionsManager::getInstance()->getWindowSize();
	this->GLWindow = glfwCreateWindow(windowSize.x, windowSize.y, "FirstProject", NULL, NULL);
	if(GLWindow == NULL)
	{
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(this->GLWindow);

//	glfwSetInputMode(this->GLWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(this->GLWindow, InputManager::mouse_pos_callback);
    glfwSetMouseButtonCallback(this->GLWindow, InputManager::mouse_button_callback);
	glfwSetKeyCallback(this->GLWindow, InputManager::key_callback);

	// Load GLAD
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Setup viewport and resizing
	glViewport(0, 0, 1600, 1200);
	glfwSetFramebufferSizeCallback(GLWindow, framebuffer_size_callback);

    glfwSetWindowSizeLimits(GLWindow, 640, 480, GLFW_DONT_CARE, GLFW_DONT_CARE);

	// Depth Testing
    if(depthTest)
	    glEnable(GL_DEPTH_TEST);

    // Turn on multisampling for MSAA
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);

    // Alpha Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Register base inputs
    InputConfig config = InputConfig();
    config.keys.push_back(KEY_ESCAPE); config.keys.push_back(KEY_F1);
	InputManager::getInstance()->registerReceiver(this, config);

    stbi_set_flip_vertically_on_load(true);
}

bool Window::shouldClose()
{
	if(glfwWindowShouldClose(this->GLWindow))
		return true;
	return false;
}

void Window::swapBuffers()
{
	glfwSwapBuffers(this->GLWindow);
}

void Window::processInput()
{
    glfwPollEvents();
}

void Window::close()
{
    glfwTerminate();
}

void Window::getCursorPosition(double* xpos, double* ypos)
{
	glfwGetCursorPos(this->GLWindow, xpos, ypos);
}

void Window::keyInputCallback(Key key, int scancode, Action action, Modifier mods)
{
	if(action != GLFW_PRESS)
		return;

	switch(key)
	{
		case KEY_ESCAPE:
			glfwSetWindowShouldClose(this->GLWindow, true);
			break;
		case KEY_F1:
			this->toggleWireframeMode();
			break;
	}
}

void Window::eventCallback(Event event)
{
    switch(event)
    {
        case QUIT_GAME:
            glfwSetWindowShouldClose(this->GLWindow, true);
            break;
        default:
            break;
    }
}

void Window::toggleWireframeMode()
{
	if(!this->wireframeMode)
	{
		std::cout << "Wireframe Mode: On" << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		this->wireframeMode = true;
	}
	else
	{
		std::cout << "Wireframe Mode: Off" << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		this->wireframeMode = false;
	}
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    OptionsManager* optionsManager = OptionsManager::getInstance();
    optionsManager->updateResolution(glm::vec2(width, height));
}
