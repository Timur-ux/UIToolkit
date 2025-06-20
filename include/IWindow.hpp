#ifndef UI_WINDOW_HPP_
#define UI_WINDOW_HPP_

/*
 * Window interface
 */

#include "IKeyboard.hpp"
#include "IMouse.hpp"

namespace ui {
class IWindow {
public:
	IWindow(IMouse &theMouse, IKeyboard &theKeyboard) : mouse(theMouse), keyboard(theKeyboard) {}
	IMouse & mouse;
	IKeyboard & keyboard;

	virtual IWindow & close() = 0;

	virtual IWindow & focus() = 0;
	virtual IWindow & minimize() = 0;

	virtual IWindow & resize(double newWidth, double newHeight) = 0;
	virtual IWindow & move(double newX, double newY) = 0;

	virtual IWindow & fullscreen() = 0; 
	virtual IWindow & windowed() = 0; 

	virtual void startRenderLoop() = 0;

	virtual ~IWindow() = default;
};
} // namespace ui
#endif // !UI_WINDOW_HPP_
