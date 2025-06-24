#include "core/Window.hpp"
#include "KeyboardDefinitions.hpp"
#include "core/Keyboard.hpp"
#include "core/Mouse.hpp"
#include "core/render/IMesh.hpp"
#include "core/render/IProgram.hpp"
#include "core/render/MeshAttributeSetters.hpp"
#include "core/render/Program.hpp"
#include "event.hpp"
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

int main(int argc, char *argw[]) {
  core::Window window(std::make_unique<core::Mouse>(),
                      std::make_unique<core::Keyboard>(),
                      "Test window functions");

	event::LambdaHandler<ui::ButtonInfo> pressHandler{[&window](ui::ButtonInfo button) {
    switch (button.key) {
    case GLFW_KEY_ESCAPE:
			window.close();
      break;
    }
	}};

	window.keyboard.onButtonPress += &pressHandler;

	std::shared_ptr<core::render::IProgram> program = std::make_shared<core::render::Program>(std::string("./shaders/coordAndColor.glsl"));
	core::render::MeshBase box{program};
	setRectangleVertexes(box, 0);
	setColor(box.attributes(), {1.0, 0.0, 0.0, 1.0}, 4, 1);
	std::function<void()> renderFunc = [&box](){
		box.render();
	};
	window.startRenderLoop(renderFunc);
	window.keyboard.onButtonPress -= &pressHandler;

  return 0;
}

