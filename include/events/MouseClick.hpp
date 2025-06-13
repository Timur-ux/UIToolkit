#ifndef EVENT_MOUSE_CLICK_HPP_
#define EVENT_MOUSE_CLICK_HPP_
#include "MouseDefinitions.hpp"
#include "events/IUIEvent.hpp"
#include <GLFW/glfw3.h>
namespace event {

class MousePress : public IUIEvent<ui::MouseButton> {
public:
  MousePress();
  ~MousePress();

  void registry(GLFWwindow *window) override;
};

class MouseRelease : public IUIEvent<ui::MouseButton> {
public:
  MouseRelease();
  ~MouseRelease();

  void registry(GLFWwindow *window) override;
};
} // namespace event
#endif // !EVENT_MOUSE_CLICK_HPP_
