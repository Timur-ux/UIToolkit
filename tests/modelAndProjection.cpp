#include "KeyboardDefinitions.hpp"
#include "core/Keyboard.hpp"
#include "core/Mouse.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/Window.hpp"
#include "core/primitives/Rectangle.hpp"
#include "core/render/Program.hpp"
#include "event.hpp"
#include "utils/strfast.hpp"
#include <GLFW/glfw3.h>
#include <functional>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <stdexcept>

int main(int argc, char *argw[]) {
  core::Window window(std::make_unique<core::Mouse>(),
                      std::make_unique<core::Keyboard>(),
                      "Test window functions");

  auto program =
      std::make_shared<core::render::Program>("./shaders/MPandColor.glsl");
  std::string projectionName = "projection";
  GLint projectionLocation = program->getUniformLocation(projectionName);
  if (projectionLocation < 0)
    throw std::runtime_error(utils::strfast()
                             << "Uniform with name [" << projectionName
                             << "] not found in program");

  float width = 800, height = 600;
  glm::mat4 projection =
      glm::ortho(-width / 2, width / 2, height / 2, -height / 2);
  auto uniformSetter = [&projection, projectionLocation](GLuint programId) {
    glProgramUniformMatrix4fv(programId, projectionLocation, 1, GL_FALSE,
                              glm::value_ptr(projection));
  };
  program->setUniform(uniformSetter);

  core::primitives::Rectangle mesh{program, {.5, .3, .7}};
  mesh.scale({width / 2, height / 2, .5});
  core::primitives::Rectangle arcs[]{
      {program, {0., 0., 1.}},
      {program, {0., 1., 0.}},
      {program, {1., 0., 0.}},
      {program, {1., 0., 1.}},
  };
  for (size_t i = 0; i < 4; ++i)
    arcs[i].scale({.5, .5, .5});

  float arcWidth = 50;
  arcs[0].scale({width, arcWidth, 1}).shiftBy({0, -height / 20, 0});
	arcs[0].moveTo({0, 0, 0});
  arcs[1].scale({arcWidth, height, 1}).shiftBy({-width / 20, 0, 0});
  arcs[2].scale({width, arcWidth, 1}).shiftBy({0, height / 20, 0});
  arcs[3].scale({arcWidth, height, 1}).shiftBy({width / 20, 0, 0});
  std::function<void()> renderFunc = [&mesh, &arcs]() {
    mesh.render();
    for (size_t i = 0; i < 4; ++i)
      arcs[i].render();
  };


  event::LambdaHandler<ui::ButtonInfo> pressHandler{
      [&window, &mesh, &width, &height](ui::ButtonInfo button) {
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
          mesh.shiftBy({50.0 / width, 0, 0});
          break;
        case GLFW_KEY_4:
          mesh.shiftBy({-50.0 / width, 0, 0});
          break;
        case GLFW_KEY_5:
          mesh.shiftBy({0, 50.0 / height, 0});
          break;
        case GLFW_KEY_6:
          mesh.shiftBy({0, -50.0 / height, 0});
          break;
        case GLFW_KEY_7:
          mesh.shiftBy({0, 0, 50.0});
          break;
        case GLFW_KEY_8:
          mesh.shiftBy({0, 0, -50.0});
          break;
        case GLFW_KEY_9:
          mesh.moveTo({0, 0, 0});
          break;
        case GLFW_KEY_0:
          mesh.moveTo({-100, -100, 0});
          break;
        }
      }};

  window.keyboard.onButtonPress += &pressHandler;
  window.startRenderLoop(renderFunc);
  window.keyboard.onButtonPress -= &pressHandler;

  return 0;
}
