#include "KeyboardDefinitions.hpp"
#include "core/Keyboard.hpp"
#include "core/Mouse.hpp"
#include "core/Window.hpp"
#include "core/primitives/Rectangle.hpp"
#include "core/render/Program.hpp"
#include "event.hpp"
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

int main(int argc, char *argw[]) {
  core::Window window(std::make_unique<core::Mouse>(),
                      std::make_unique<core::Keyboard>(),
                      "Test window functions");

  auto program =
      std::make_shared<core::render::Program>("./shaders/modelAndColor.glsl");

	core::primitives::Rectangle mesh{program, {.5, .3, .7}};
  std::function<void()> renderFunc = [&]() { mesh.render(); };

  event::LambdaHandler<ui::ButtonInfo> pressHandler{
      [&window, &mesh](ui::ButtonInfo button) {
        switch (button.key) {
        case GLFW_KEY_ESCAPE:
          window.close();
          break;
				case GLFW_KEY_1:
					mesh.scale({.5, .5, .5});
					break;
				case GLFW_KEY_2:
					mesh.scale({2, 2, 2});
					break;
				case GLFW_KEY_3:
					mesh.shiftBy({.3, 0, 0});
					break;
				case GLFW_KEY_4:
					mesh.shiftBy({-.3, 0, 0});
					break;
				case GLFW_KEY_5:
					mesh.shiftBy({0, .3, 0});
					break;
				case GLFW_KEY_6:
					mesh.shiftBy({0, -.3, 0});
					break;
				case GLFW_KEY_7:
					mesh.moveTo({0, 0, 0});
					break;
        }
      }};

  window.keyboard.onButtonPress += &pressHandler;
  window.startRenderLoop(renderFunc);
  window.keyboard.onButtonPress -= &pressHandler;

  return 0;
}


