// --------------
// |  mouse up  |
// --------------

#include "events/MouseClick.hpp"
#include "MouseDefinitions.hpp"
#include <GLFW/glfw3.h>
#include <memory>
using namespace event;

static MouseRelease *mouseUpEvent = nullptr;

MouseRelease::MouseRelease() { mouseUpEvent = this; }

MouseRelease::~MouseRelease() { mouseUpEvent = nullptr; }

void mouseCallback(GLFWwindow *window, int button, int action, int mods);

void MouseRelease::registry(GLFWwindow *window) {
  glfwSetMouseButtonCallback(window, mouseCallback);
}

// ----------------
// |  mouse down  |
// ----------------

static MousePress *mouseDownEvent = nullptr;

MousePress::MousePress() { mouseDownEvent = this; }

MousePress::~MousePress() { mouseDownEvent = nullptr; }

void mouseCallback(GLFWwindow *window, int button, int action, int mods);

void MousePress::registry(GLFWwindow *window) {
  glfwSetMouseButtonCallback(window, mouseCallback);
}

// --------------
// |  callback  |
// --------------

void mouseCallback(GLFWwindow *window, int button, int action, int mods) {
  ui::MouseButton mouseButton;
  switch (button) {
  case GLFW_MOUSE_BUTTON_LEFT:
    mouseButton = ui::MouseButton::LEFT_BUTTON;
    break;
  case GLFW_MOUSE_BUTTON_RIGHT:
    mouseButton = ui::MouseButton::RIGHT_BUTTON;
    break;
  default:
    return;
  }

  if (action == GLFW_PRESS && mouseDownEvent) 
		mouseDownEvent->invoke(mouseButton);
	if(action == GLFW_RELEASE && mouseUpEvent) 
		mouseUpEvent->invoke(mouseButton);
}
