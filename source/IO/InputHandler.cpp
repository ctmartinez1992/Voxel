#include "InputHandler.h"

InputHandler* InputHandler::_instance = NULL;

InputHandler::InputHandler() : 
							mouseLeft(GLFW_MOUSE_BUTTON_LEFT), mouseRight(GLFW_MOUSE_BUTTON_RIGHT), mouseMiddle(GLFW_MOUSE_BUTTON_MIDDLE),
							moveForward(1), moveBack(2), moveLeft(3), moveRight(4), moveUp(5), moveDown(6)
{        
	keys[InputHandler::moveForward] = 87;
	keys[InputHandler::moveBack] = 83;
	keys[InputHandler::moveLeft] = 65;
	keys[InputHandler::moveRight] = 68;
	keys[InputHandler::moveUp] = 81;
	keys[InputHandler::moveDown] = 90;
}

InputHandler::~InputHandler() {
}

InputHandler* InputHandler::getInstance() {
   if (!_instance) {
      _instance = new InputHandler;
   }
   return _instance;
}

bool InputHandler::keyPressed(int key) {
	return glfwGetKey(keys[key]);
}

bool InputHandler::mousePressed(int key) const {
	return glfwGetMouseButton(key);
}

void InputHandler::setMouseWheelValue(const float value) {
	glfwSetMouseWheel(0);
}

float InputHandler::getMouseWheelValue() const {
	return (float) glfwGetMouseWheel();
}

void InputHandler::setMousePosition(const int x, const int y) {
	glfwSetMousePos(x, y);
}

void InputHandler::getMousePosition(int& x, int& y) const {
	glfwGetMousePos(&x, &y);
}