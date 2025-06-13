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
	event::IEvent<ButtonInfo> &onButtonPress;
	event::IEvent<ButtonInfo> &onButtonRelease;
};
} // namespace ui

#endif // !UI_KEYBOARD_HPP_
