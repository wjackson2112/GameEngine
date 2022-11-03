#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include "Scene.h"
#include "IInputReceiver.h"

// Don't show a cmd window when starting up (WINDOWS Only)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

class Window: public IInputReceiver
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
	void keyInputCallback(int key, int scancode, int action, int mods);

	// Callback to handle resizing GL with the window
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
};

#endif
