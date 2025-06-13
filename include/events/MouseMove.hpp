#ifndef EVENT_MOUSE_MOVE_HPP_
#define EVENT_MOUSE_MOVE_HPP_
#include "MouseDefinitions.hpp"
#include "events/IUIEvent.hpp"
#include <GLFW/glfw3.h>
#include <memory>
namespace event {

class MouseMove : public IUIEvent<ui::MousePosition> {
	static double x_, y_;
public:
  MouseMove();
  ~MouseMove();

  void registry(GLFWwindow *window) override;
  void updatePosition(double newX, double newY);
};
} // namespace event
#endif // !EVENT_MOUSE_MOVE_HPP_
