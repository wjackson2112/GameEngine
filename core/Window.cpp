#include "Window.h"

#include <iostream>
#include "Globals.h"
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

	// Configure Emscripten callbacks
#ifdef __EMSCRIPTEN__
	emscripten_set_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, Window::em_fullscreenchange_callback);
	emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, Window::em_on_canvas_resize);
	emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, InputManager::em_keydown);
#endif

	// Load GLAD
#ifndef __EMSCRIPTEN__
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
#endif

	// Setup viewport and resizing
	glViewport(0, 0,
	           OptionsManager::getInstance()->getViewportResolution().x,
	           OptionsManager::getInstance()->getViewportResolution().y);
	glfwSetFramebufferSizeCallback(GLWindow, framebuffer_size_callback);

    glfwSetWindowSizeLimits(GLWindow, 640, 480, GLFW_DONT_CARE, GLFW_DONT_CARE);

	// Depth Testing
    if(depthTest)
        glEnable(GL_DEPTH_TEST);

    // Turn on multisampling for MSAA
    glfwWindowHint(GLFW_SAMPLES, 4);
#ifndef __EMSCRIPTEN__
    glEnable(GL_MULTISAMPLE);
#endif

    // Alpha Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    stbi_set_flip_vertically_on_load(true);

    // VSync off
#ifndef __EMSCRIPTEN__
    glfwSwapInterval(0);
#endif
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
    InputManager::getInstance()->pollGamepad();
}

void Window::close()
{
    glfwTerminate();
}

void Window::getCursorPosition(double* xpos, double* ypos)
{
	glfwGetCursorPos(this->GLWindow, xpos, ypos);
}

void Window::eventCallback(Event event)
{
    switch(event)
    {
        case Event::EVT_QUIT_GAME:
            glfwSetWindowShouldClose(this->GLWindow, true);
            break;
        case Event::EVT_WIREFRAME_MODE:
            this->toggleWireframeMode();
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
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		this->wireframeMode = true;
	}
	else
	{
		std::cout << "Wireframe Mode: Off" << std::endl;
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		this->wireframeMode = false;
	}
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    OptionsManager* optionsManager = OptionsManager::getInstance();
    optionsManager->updateResolution(glm::vec2(width, height));
}

#ifdef __EMSCRIPTEN__
bool Window::em_fullscreenchange_callback(int eventType, const EmscriptenFullscreenChangeEvent *e, void *userData)
{
	glViewport(0, 0, e->screenWidth, e->screenHeight);

	OptionsManager* optionsManager = OptionsManager::getInstance();
	optionsManager->updateResolution(glm::vec2(e->screenWidth, e->screenHeight));

	return true;
}

bool Window::em_on_canvas_resize(int eventType, const EmscriptenUiEvent *e, void *userData)
{
	EmscriptenFullscreenChangeEvent fs_status;
	EMSCRIPTEN_RESULT result = emscripten_get_fullscreen_status(&fs_status);
	if(result == EMSCRIPTEN_RESULT_SUCCESS && fs_status.isFullscreen)
	{
		return EM_FALSE;
	}

	glViewport(0, 0, e->windowInnerWidth, e->windowInnerHeight);
	glfwSetWindowSize(GWindow.GLWindow, e->windowInnerWidth, e->windowInnerHeight);

	OptionsManager* optionsManager = OptionsManager::getInstance();
	optionsManager->updateResolution(glm::vec2(e->windowInnerWidth, e->windowInnerHeight));

	return EM_TRUE;
}
#endif
