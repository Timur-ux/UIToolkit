#include "events/KeyboardClick.hpp"
#include "KeyboardDefinitions.hpp"
#include <GLFW/glfw3.h>

using namespace event;

static KeyboardPress *pressEvent = nullptr;
static KeyboardRelease *releaseEvent = nullptr;
void callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// --------------------
// |  keyboard press  |
// --------------------

KeyboardPress::KeyboardPress() { pressEvent = this; }

KeyboardPress::~KeyboardPress() { pressEvent = nullptr; }

void KeyboardPress::registry(GLFWwindow *window) {
  glfwSetKeyCallback(window, callback);
}

// --------------------
// |  keyboard release  |
// --------------------

KeyboardRelease::KeyboardRelease() { releaseEvent = this; }

KeyboardRelease::~KeyboardRelease() { releaseEvent = nullptr; }

void KeyboardRelease::registry(GLFWwindow *window) {
  glfwSetKeyCallback(window, callback);
}

// --------------
// |  callback  |
// --------------

void callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if (action == GLFW_PRESS && pressEvent)
    pressEvent->invoke(ui::ButtonInfo{key});

  if (action == GLFW_RELEASE && releaseEvent)
    releaseEvent->invoke(ui::ButtonInfo{key});
}
