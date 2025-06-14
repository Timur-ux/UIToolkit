#include "core/Mouse.hpp"
#include "MouseDefinitions.hpp"
#include "event.hpp"
#include <memory>
#include <set>
#include <utility>
#ifdef DEBUG
#include <iostream>
#endif

using namespace core;

namespace impl {
struct MouseHandler {
  event::LambdaHandler<ui::MousePosition> positionHandler_{
      [this](ui::MousePosition position) { this->position = position;
			}};
  event::LambdaHandler<ui::MouseButton> pressHandler_{
      [this](ui::MouseButton button) { this->pressedButtons.insert(button); 
			#ifdef DEBUG
				std::cout << "Mouse pressed: " << (int)button << std::endl;
			#endif
			}};
  event::LambdaHandler<ui::MouseButton> releaseHandler_{
      [this](ui::MouseButton button) { this->pressedButtons.erase(button); 
			#ifdef DEBUG
				std::cout << "Mouse released: " << (int)button<< std::endl;
			#endif
			}};

  ui::MousePosition position;
  std::set<ui::MouseButton> pressedButtons;
};
} // namespace impl

Mouse::Mouse()
    : ui::IMouse(onMove_, onPress_, onRelease_)
		, handler_(std::move(std::make_unique<impl::MouseHandler>()))
{
  onMove += &handler_->positionHandler_;
  onPress_ += &handler_->pressHandler_;
  onRelease_ += &handler_->releaseHandler_;
}

Mouse::~Mouse() {
  onMove -= &handler_->positionHandler_;
  onPress_ -= &handler_->pressHandler_;
  onRelease_ -= &handler_->releaseHandler_;
}

ui::MousePosition Mouse::position() const { return handler_->position; }

bool Mouse::isPressed(ui::MouseButton button) const {
  return handler_->pressedButtons.contains(button);
}

bool Mouse::isReleased(ui::MouseButton button) const {
  return !isPressed(button);
}

void Mouse::registryEvents(GLFWwindow *window) {
  onMove_.registry(window);
  onPress_.registry(window);
  onRelease_.registry(window);
}
