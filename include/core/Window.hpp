#ifndef OPENGL_WINDOW_HPP_
#define OPENGL_WINDOW_HPP_

/*
 * GLFW based window implementation
 */

#include "IWindow.hpp"
#include "OpenGLHeaders.hpp"

namespace core {
class Window : public ui::IWindow {
  GLFWwindow *window_ = 0;

	int windowX_ = 0, windowY_ = 0;
	int height_ = 600, width_ = 800;

	void destroy();
	void updateViewport();
public:
  Window(ui::IMouse &theMouse, ui::IKeyboard &theKeyboard, std::string title,
         int width = 800, int height = 600, bool resizeable = true);
  ~Window();

  IWindow &focus() override;
  IWindow &minimize() override;

  IWindow &resize(double newWidth, double newHeight) override;
  IWindow &move(double newX, double newY) override;

  IWindow &fullscreen() override;
  IWindow &windowed() override;
	
	void startRenderLoop() override;
};
} // namespace core
#endif // !OPENGL_WINDOW_HPP_
