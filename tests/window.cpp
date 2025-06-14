#include "core/Window.hpp"
#include "KeyboardDefinitions.hpp"
#include "core/Keyboard.hpp"
#include "core/Mouse.hpp"
#include "event.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

int main(int argc, char *argw[]) {
  core::Window window(std::make_unique<core::Mouse>(),
                      std::make_unique<core::Keyboard>(),
                      "Test window functions");

  std::cout << "Input [1] to focus window\n";
  std::cout << "Input [2] to minimize window\n";
  std::cout << "Input [3] to fullscreen window\n";
  std::cout << "Input [4] to windowed window\n";

  std::cout << "Input [5] to increase width by 100 px\n";
  std::cout << "Input [6] to decrease width by 100 px\n";
  std::cout << "Input [7] to increase height by 100 px\n";
  std::cout << "Input [8] to decrease height by 100 px\n";

  std::cout << "Input [9] to increase x and y by 100 px\n";
  std::cout << "Input [0] to decrease x and y by 100 px\n";

  std::cout << "Input [m] to print mouse position\n";
  std::cout << "Input [<ESC>] to close window and stop test\n";


	event::LambdaHandler<ui::ButtonInfo> pressHandler{[&window](ui::ButtonInfo button) {
		auto size = window.size();
		auto pos = window.position();
    switch (button.key) {
    case GLFW_KEY_1:
      window.focus();
      break;
    case GLFW_KEY_2:
      window.minimize();
      break;
    case GLFW_KEY_3:
      window.fullscreen();
      break;
    case GLFW_KEY_4:
      window.windowed();
      break;
    case GLFW_KEY_5:
			size.width += 100;
      window.resize(size.width, size.height);
      break;
    case GLFW_KEY_6:
			size.width -= 100;
      window.resize(size.width, size.height);
      break;
    case GLFW_KEY_7:
			size.height += 100;
      window.resize(size.width, size.height);
      break;
    case GLFW_KEY_8:
			size.height -= 100;
      window.resize(size.width, size.height);
      break;

    case GLFW_KEY_9:
			pos.x += 100;
			pos.y += 100;
      window.move(pos.x, pos.y);
      break;
    case GLFW_KEY_0:
			pos.x -= 100;
			pos.y -= 100;
      window.move(pos.x, pos.y);
      break;
    case GLFW_KEY_M:
			std::cout << window.mouse.position().x << ' ' << window.mouse.position().y << std::endl;
      break;
    case GLFW_KEY_ESCAPE:
			window.close();
      break;
    default:
      std::cout << "Unrecognized button: " << button.key << std::endl;
      break;
    }
	}};

	window.keyboard.onButtonPress += &pressHandler;
	window.startRenderLoop();
	window.keyboard.onButtonPress -= &pressHandler;

  return 0;
}
