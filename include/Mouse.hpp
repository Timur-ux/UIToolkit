#ifndef UI_MOUSE_HPP_
#define UI_MOUSE_HPP_

/*
 * Mouse interface
 */

#include "event.hpp"

namespace ui {
enum class MouseButton {
	LEFT_BUTTON,
	RIGHT_BUTTION
};

struct MousePosition {
	double x, y;
};

class IMouse {
public:
	event::IEvent<MousePosition> &onMove;
	event::IEvent<MouseButton, MousePosition> &onMouseButtonDown;
	event::IEvent<MouseButton, MousePosition> &onMouseButtonUp;
};
} // namespace ui
#endif // !UI_MOUSE_HPP_
