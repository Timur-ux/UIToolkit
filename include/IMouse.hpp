#ifndef UI_MOUSE_HPP_
#define UI_MOUSE_HPP_

/*
 * Mouse interface
 */

#include "MouseDefinitions.hpp"
#include "event.hpp"

namespace ui {
class IMouse {
public:
	event::IEvent<MousePosition> &onMove;
	event::IEvent<MouseButton> &onMouseButtonPress;
	event::IEvent<MouseButton> &onMouseButtonRelease;
};
} // namespace ui
#endif // !UI_MOUSE_HPP_
