#ifndef MOUSE_DEFINITIONS_HPP_
#define MOUSE_DEFINITIONS_HPP_
namespace ui {
enum class MouseButton {
	LEFT_BUTTON,
	RIGHT_BUTTON
};

struct MousePosition {
	double x, y;
};
} // namespace ui

#endif // !MOUSE_DEFINITIONS_HPP_
