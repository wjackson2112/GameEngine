#ifndef WINDOW_H
#define WINDOW_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "IEventReceiver.h"

// Don't show a cmd window when starting up (WINDOWS Only)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

class Window: public IEventReceiver
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
	GLFWwindow* getGLFWWindow() { return GLWindow; };
 
public:
	void toggleWireframeMode();
private:
	bool wireframeMode;

public:
    //IEventReceiver
    void eventCallback(Event event) override;

	// Callback to handle resizing GL with the window
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#ifdef __EMSCRIPTEN__
	static bool em_fullscreenchange_callback(int eventType, const EmscriptenFullscreenChangeEvent *e, void *userData);
	static bool em_on_canvas_resize(int eventType, const EmscriptenUiEvent *e, void *userData);
#endif

};

#endif
