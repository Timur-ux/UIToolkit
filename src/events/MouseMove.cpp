#include "events/MouseMove.hpp"
#include "MouseDefinitions.hpp"
#include <GLFW/glfw3.h>
#include <memory>
using namespace event;

static MouseMove *mouseEvent = nullptr;

MouseMove::MouseMove() { mouseEvent = this; }

MouseMove::~MouseMove() { mouseEvent = nullptr; }

void MouseMove::updatePosition(double newX, double newY) {
  x_ = newX, y_ = newY;
  invoke(ui::MousePosition{x_, y_});
}

void callback(GLFWwindow *window, double x, double y) {
  if (mouseEvent)
    mouseEvent->updatePosition(x, y);
}

void MouseMove::registry(GLFWwindow *window) {
  glfwSetCursorPosCallback(window, callback);
}

std::shared_ptr<MouseMove> MouseMove::instance_ = std::make_shared<MouseMove>();
