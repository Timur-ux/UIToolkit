#ifndef UI_KEYBOARD_HPP_
#define UI_KEYBOARD_HPP_

/*
 * Keyboard interface
 * ButtonInfo may be extended in future by new data
 */

#include "event.hpp"
struct ButtonInfo {
	int code;
};

class IKeyboard {
public:
	event::IEvent<ButtonInfo> &onButtonPress;
	event::IEvent<ButtonInfo> &onButtonRelease;
};

#endif // !UI_KEYBOARD_HPP_
