#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <vector>
#include "maths/Vec2.h"

class InputReciever;

class Input {
public:
	static void initialise(GLFWwindow* handle);
	static bool isKeyPressed(int keyCode);
	static bool isMouseButtonPressed(int buttonCode);
	static Vec2 getMousePosition();
	static void registerReciever(InputReciever* reciever);
	static void deregisterReciever(InputReciever* reciever);

	static std::vector<InputReciever*> s_recievers;
private:
	static GLFWwindow* s_handle;
};

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mod);

#endif