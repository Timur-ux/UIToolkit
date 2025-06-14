#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

/*
 * GLFW based keyboard implementation
 */

#include "IKeyboard.hpp"
#include "KeyboardDefinitions.hpp"
#include "events/KeyboardClick.hpp"
#include <memory>

namespace impl {
struct KeyboardHandler;
} // namespace impl

namespace core {
class Keyboard : public ui::IKeyboard {
	event::KeyboardPress onPress_;
	event::KeyboardRelease onRelease_;

	std::unique_ptr<impl::KeyboardHandler> handler_;
public:
	Keyboard();
	~Keyboard();

	bool isPressed(ui::ButtonInfo button) override;
	bool isReleased(ui::ButtonInfo button) override;

	void registryEvents(GLFWwindow * window); 
};
} // namespace core
#endif // !KEYBOARD_HPP_
