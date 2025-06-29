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
                      "Projection based moving test");

  auto program =
      std::make_shared<core::render::Program>("./shaders/MPandColor.glsl");
  std::string projectionName = "projection";
  GLint projectionLocation = program->getUniformLocation(projectionName);
  if (projectionLocation < 0)
    throw std::runtime_error(utils::strfast()
                             << "Uniform with name [" << projectionName
                             << "] not found in program");

  float width = 800, height = 600, depth = 400;
  glm::mat4 projection = glm::ortho(0.0f, width, height, 0.0f, -depth/2, depth/2);
  auto uniformSetter = [&projection, projectionLocation](GLuint programId) {
    glProgramUniformMatrix4fv(programId, projectionLocation, 1, GL_FALSE,
                              glm::value_ptr(projection));
  };
  program->setUniform(uniformSetter);
	glEnable(GL_DEPTH_TEST);

  core::primitives::Rectangle mesh{program, {.5, .3, .7}};
  mesh.scale({50.0, 50.0, 1});

  float arcWidth = 50;
	core::primitives::Rectangle arcs[] = {
		{program, {1, 0, 0}},
		{program, {1, 0, 0}},
		{program, {1, 0, 0}},
		{program, {1, 0, 0}},
	};

	arcs[0].scale({width, arcWidth, 1}).moveTo({0, 0 , 0});
	arcs[1].scale({width, arcWidth, 1}).moveTo({0, height - arcWidth, 0});
	arcs[2].scale({arcWidth, height, 1}).moveTo({0, 0 , 0});
	arcs[3].scale({arcWidth, height, 1}).moveTo({width - arcWidth, 0 , 0});
	
  std::function<void()> renderFunc = [&]() {
		mesh.render();
		for(size_t i = 0; i < 4; ++i) 
			arcs[i].render();
	};

	float stepSize = 50;

  event::LambdaHandler<ui::ButtonInfo> pressHandler{
      [&window, &mesh, &width, &height, &stepSize](ui::ButtonInfo button) {
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
        case GLFW_KEY_RIGHT:
          mesh.shiftBy({stepSize, 0, 0});
          break;
        case GLFW_KEY_LEFT:
          mesh.shiftBy({-stepSize, 0, 0});
          break;
        case GLFW_KEY_DOWN:
          mesh.shiftBy({0, stepSize, 0});
          break;
        case GLFW_KEY_UP:
          mesh.shiftBy({0, -stepSize, 0});
          break;
        case GLFW_KEY_J:
          mesh.shiftBy({0, 0, stepSize});
          break;
        case GLFW_KEY_K:
          mesh.shiftBy({0, 0, -stepSize});
          break;
        case GLFW_KEY_R:
          mesh.moveTo({0, 0, 0});
          break;
				case GLFW_KEY_A:
					stepSize *= 2;
					std::cout << "Step size: " << stepSize << std::endl;
					break;
				case GLFW_KEY_B:
					stepSize /= 2;
					std::cout << "Step size: " << stepSize << std::endl;
					break;
        }

				std::cout << mesh.position() << std::endl;
      }};

  window.keyboard.onButtonPress += &pressHandler;
  window.startRenderLoop(renderFunc);
  window.keyboard.onButtonPress -= &pressHandler;

  return 0;
}
