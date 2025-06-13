#ifndef UI_EVENT_BASE_HPP_
#define UI_EVENT_BASE_HPP_

/*
 * UI event interface to work with glfw events
 */

#include "event.hpp"
#include <GLFW/glfw3.h>

namespace event {
template <typename ...Args>
class IUIEvent : public Event<Args...> {
public:
	virtual void registry(GLFWwindow * window) = 0;
};
} // namespace core
#endif // !UI_EVENT_BASE_HPP_
