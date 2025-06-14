#ifndef MOUSE_HPP_
#define MOUSE_HPP_
/*
 * Event based mouse implementation
 */

#include "IMouse.hpp"
#include "events/MouseClick.hpp"
#include "events/MouseMove.hpp"
#include <GLFW/glfw3.h>
#include <memory>
namespace impl {
struct MouseHandler;
} // namespace impl
	
namespace core {
class Mouse : public ui::IMouse {
  event::MouseMove onMove_;
  event::MousePress onPress_;
  event::MouseRelease onRelease_;

	std::unique_ptr<impl::MouseHandler> handler_;
public:
  Mouse();
  ~Mouse();

	ui::MousePosition position() const override;
	bool isPressed(ui::MouseButton) const override;
	bool isReleased(ui::MouseButton) const override;

	void registryEvents(GLFWwindow * window);
};
} // namespace core
#endif // !MOUSE_HPP_
