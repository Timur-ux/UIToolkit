#include "core/Keyboard.hpp"
#include "IKeyboard.hpp"
#include "KeyboardDefinitions.hpp"
#include <memory>

#ifdef DEBUG
#include <iostream>
#endif

using namespace core;

namespace impl {
struct KeyboardHandler {
  event::LambdaHandler<ui::ButtonInfo> pressHandler_{
      [this](ui::ButtonInfo button) {
        this->pressedButtons[button.key] = true;
#ifdef DEBUG
				std::cout << "Pressed: " << button.key<< std::endl;
#endif
      }};
  event::LambdaHandler<ui::ButtonInfo> releaseHandler_{
      [this](ui::ButtonInfo button) {
        this->pressedButtons[button.key] = false;
#ifdef DEBUG
				std::cout << "Released: " << button.key<< std::endl;
#endif
      }};
  std::vector<bool> pressedButtons;

  static size_t n_buttons;

  KeyboardHandler() {
    pressedButtons.assign(KeyboardHandler::n_buttons, false);
  }
};

size_t KeyboardHandler::n_buttons = 1024;
} // namespace impl

Keyboard::Keyboard()
    : ui::IKeyboard(onPress_, onRelease_),
      handler_(std::move(std::make_unique<impl::KeyboardHandler>())) {
  onPress_ += &handler_->pressHandler_;
  onRelease_ += &handler_->releaseHandler_;
}

Keyboard::~Keyboard() {
  onPress_ -= &handler_->pressHandler_;
  onRelease_ -= &handler_->releaseHandler_;
}

bool Keyboard::isPressed(ui::ButtonInfo button) {
  return handler_->pressedButtons.at(button.key);
}

bool Keyboard::isReleased(ui::ButtonInfo button) { return !isPressed(button); }

void Keyboard::registryEvents(GLFWwindow *window) {
  onPress_.registry(window);
  onRelease_.registry(window);
}
