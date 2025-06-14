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
  IMouse(event::IEvent<MousePosition> &onMove_,
         event::IEvent<MouseButton> &onMouseButtonPress_,
         event::IEvent<MouseButton> &onMouseButtonRelease_)
      : onMove(onMove_), onMouseButtonPress(onMouseButtonPress_),
        onMouseButtonRelease(onMouseButtonRelease_) {}

  event::IEvent<MousePosition> &onMove;
  event::IEvent<MouseButton> &onMouseButtonPress;
  event::IEvent<MouseButton> &onMouseButtonRelease;

  virtual MousePosition position() const = 0;
  virtual bool isPressed(MouseButton) const = 0;
  virtual bool isReleased(MouseButton) const = 0;
};
} // namespace ui
#endif // !UI_MOUSE_HPP_
