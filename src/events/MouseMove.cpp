#include "events/MouseMove.hpp"
#include "MouseDefinitions.hpp"
#include <GLFW/glfw3.h>
using namespace event;

static MouseMove *mouseEvent = nullptr;

MouseMove::MouseMove() { mouseEvent = this; }

MouseMove::~MouseMove() { mouseEvent = nullptr; }

void callback(GLFWwindow *window, double x, double y) {
  if (mouseEvent)
    mouseEvent->invoke(ui::MousePosition{.x = x, .y = y});
}

void MouseMove::registry(GLFWwindow *window) {
  glfwSetCursorPosCallback(window, callback);
}
