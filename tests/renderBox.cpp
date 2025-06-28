#include "KeyboardDefinitions.hpp"
#include "core/Keyboard.hpp"
#include "core/MeshBase.hpp"
#include "core/Mouse.hpp"
#include "core/OpenGLHeaders.hpp"
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

  event::LambdaHandler<ui::ButtonInfo> pressHandler{
      [&window](ui::ButtonInfo button) {
        switch (button.key) {
        case GLFW_KEY_ESCAPE:
          window.close();
          break;
        }
      }};

  window.keyboard.onButtonPress += &pressHandler;

  auto program =
      std::make_shared<core::render::Program>("./shaders/coordAndColor.glsl");

	core::primitives::Rectangle mesh{program, {.5, .3, .7}};
  std::function<void()> renderFunc = [&]() { mesh.render(); };

  window.startRenderLoop(renderFunc);
  window.keyboard.onButtonPress -= &pressHandler;

  return 0;
}

