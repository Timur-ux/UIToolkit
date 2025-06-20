#ifndef UI_KEYBOARD_HPP_
#define UI_KEYBOARD_HPP_

/*
 * Keyboard interface
 * ButtonInfo may be extended in future by new data
 */

#include "KeyboardDefinitions.hpp"
#include "event.hpp"
namespace ui {

class IKeyboard {
public:
  IKeyboard(event::IEvent<ButtonInfo> &onButtonPress_,
            event::IEvent<ButtonInfo> &onButtonRelease_)
      : onButtonPress(onButtonPress_), onButtonRelease(onButtonRelease_) {}

  event::IEvent<ButtonInfo> &onButtonPress;
  event::IEvent<ButtonInfo> &onButtonRelease;

  virtual bool isPressed(ButtonInfo button) = 0;
  virtual bool isReleased(ButtonInfo button) = 0;


	virtual ~IKeyboard() = default;
};
} // namespace ui

#endif // !UI_KEYBOARD_HPP_
