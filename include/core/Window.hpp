#ifndef OPENGL_WINDOW_HPP_
#define OPENGL_WINDOW_HPP_

/*
 * GLFW based window implementation
 */

#include "IWindow.hpp"
#include "OpenGLHeaders.hpp"
#include "core/Keyboard.hpp"
#include "core/Mouse.hpp"
#include <memory>

namespace core {
class Window : public ui::IWindow {
  GLFWwindow *window_ = 0;

  int windowX_ = 0, windowY_ = 0;
  int height_ = 600, width_ = 800;

  std::unique_ptr<core::Mouse> mouse_;
  std::unique_ptr<core::Keyboard> keyboard_;

  void updateViewport();

public:
  struct Size {
    int width, height;
  };

  struct Position {
    int x, y;
  };

  Window(std::unique_ptr<core::Mouse> &&theMouse,
         std::unique_ptr<core::Keyboard> &&theKeyboard, std::string title,
         int width = 800, int height = 600, bool resizeable = true);
  ~Window();

	IWindow & close() override;

  IWindow &focus() override;
  IWindow &minimize() override;

  IWindow &resize(double newWidth, double newHeight) override;
  IWindow &move(double newX, double newY) override;

  IWindow &fullscreen() override;
  IWindow &windowed() override;

  void startRenderLoop(std::function<void()> & renderFunc) override;

  Size size() const { return Size{.width = width_, .height = height_}; }
	Position position() const {return Position{.x = windowX_, .y = windowY_};}
};
} // namespace core
#endif // !OPENGL_WINDOW_HPP_
