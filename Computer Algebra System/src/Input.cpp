#include "Input.h"
#include "graphics/Camera2D.h"

void Input::initialise(GLFWwindow* handle) {
	s_handle = handle;
	glfwSetScrollCallback(s_handle, scrollCallback);
	glfwSetMouseButtonCallback(s_handle, mouseButtonCallback);
}

bool Input::isKeyPressed(int keyCode) {
	return (glfwGetKey(s_handle, keyCode) == GLFW_PRESS);
}

bool Input::isMouseButtonPressed(int buttonCode) {
	return (glfwGetMouseButton(s_handle, buttonCode) == GLFW_PRESS);
}

Vec2 Input::getMousePosition() {
	double x, y;
	glfwGetCursorPos(s_handle, &x, &y);
	return { static_cast<float>(x), static_cast<float>(y) };
}

void Input::registerReciever(InputReciever* reciever) {
	s_recievers.push_back(reciever);
}

void Input::deregisterReciever(InputReciever* reciever)
{
	s_recievers.erase(std::remove(s_recievers.begin(), s_recievers.end(), reciever));
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	for (auto reciever : Input::s_recievers) {
		reciever->onScroll(static_cast<float>(yOffset));
	}
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mod) {
	for (auto reciever : Input::s_recievers) {
		reciever->onMouseClick(button, action);
	}
}

GLFWwindow* Input::s_handle = nullptr;
std::vector<InputReciever*> Input::s_recievers;