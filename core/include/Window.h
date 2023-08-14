#ifndef WINDOW_H
#define WINDOW_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW\glfw3.h>

#include "Scene.h"
#include "IInputReceiver.h"
#include "IEventReceiver.h"

// Don't show a cmd window when starting up (WINDOWS Only)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

class Window: public IInputReceiver, public IEventReceiver
{
	GLFWwindow* GLWindow;
//	std::vector<Scene*> scenes;
//	Scene* activeScene = nullptr;

public:
	Window(bool depthTest = true);

//	void addScene(Scene* scene);
//	void draw();
//	void update();

	bool shouldClose();
	void swapBuffers();
    void processInput();
    void close();

	void getCursorPosition(double* xpos, double* ypos);
 
public:
	void toggleWireframeMode();
private:
	bool wireframeMode;

public:
	//IInputReceiver
	void keyInputCallback(Key key, int scancode, Action action, Modifier mods);

    //IEventReceiver
    void eventCallback(Event event);

	// Callback to handle resizing GL with the window
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};

#endif
