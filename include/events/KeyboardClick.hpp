#ifndef EVENT_KEYBOARD_PRESS_HPP_
#define EVENT_KEYBOARD_PRESS_HPP_
#include "KeyboardDefinitions.hpp"
#include "events/IUIEvent.hpp"
namespace event {
class KeyboardPress : public IUIEvent<ui::ButtonInfo> {
public:
	KeyboardPress();
	~KeyboardPress();

	void registry(GLFWwindow *window) override;
};


class KeyboardRelease : public IUIEvent<ui::ButtonInfo> {
public:
	KeyboardRelease();
	~KeyboardRelease();

	void registry(GLFWwindow *window) override;
};
} // namespace event
#endif // !EVENT_KEYBOARD_PRESS_HPP_
