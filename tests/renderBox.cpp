#include "KeyboardDefinitions.hpp"
#include "core/Keyboard.hpp"
#include "core/MeshBase.hpp"
#include "core/Mouse.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/Window.hpp"
#include "core/render/IMesh.hpp"
#include "core/render/Program.hpp"
#include "event.hpp"
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>
#include <vector>

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
  std::vector<glm::vec3> coords = {
      // x, y, z
      {1, -1, 0},
      {-1, -1, 0},
      {1, 1, 0},
      {-1, 1, 0},
  };

  std::vector<glm::vec3> colors = {
      // r, g, b
      {0, 1, 0},
      {0, 0, 0},
      {0, 0, 1},
      {1, 0, 1},
  };

  std::vector<GLubyte> indexes = {0, 1, 2, 3};

  // ----------------
  // |  Data setup  |
  // ----------------

  core::render::MeshBase<core::render::RenderType::TRIANGLE_STRIP> mesh{program};
  mesh.setVertexes(coords, indexes);
  mesh.setColor(colors);
  // -----------------
  // |  Render func  |
  // -----------------
  std::function<void()> renderFunc = [&]() { mesh.render(); };

  window.startRenderLoop(renderFunc);
  window.keyboard.onButtonPress -= &pressHandler;

  return 0;
}

