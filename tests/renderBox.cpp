#include "IBindable.hpp"
#include "KeyboardDefinitions.hpp"
#include "core/Keyboard.hpp"
#include "core/Mouse.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/Window.hpp"
#include "core/render/Attribute.hpp"
#include "core/render/Program.hpp"
#include "core/render/VAO.hpp"
#include "core/render/VBO.hpp"
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

  core::render::VertexArrayObject vao;
  core::render::VertexBufferObject<GL_ARRAY_BUFFER, GL_STATIC_DRAW> vbo{};
  core::render::VertexBufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_READ>
      indexVbo{};

  core::render::Program program("./shaders/coordAndColor.glsl");
  GLfloat coords[] = {// x, y, z
                      -.5, -.5, 0, .5, -.5, 0, .5, .5, 0, -.5, .5, 0};

  GLfloat colors[] = {// r, g, b
                      1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1};

  GLubyte indexes[] = {0, 1, 2, 3};

  // ----------------
  // |  Data setup  |
  // ----------------

  vbo.setData(sizeof(coords) + sizeof(colors), NULL);
  vbo.copySubData(0, sizeof(coords), coords);
  vbo.copySubData(sizeof(coords), sizeof(colors), colors);

  indexVbo.bind();
  indexVbo.setData(sizeof(indexes), indexes);

  // --------------
  // |  VAO init  |
  // --------------
  {
    BindLock<GLuint> lock1(vao);
    {
      vbo.bind(), indexVbo.bind();
      core::render::Attribute<GLfloat, 3, false> coordAttrib{0};
      core::render::Attribute<GLfloat, 4, false> colorAttrib{1};
      vbo.setVertexAttribute(coordAttrib, 0);
      vbo.setVertexAttribute(colorAttrib, (const void *)sizeof(coords));
    }
  }
  vbo.unbind(), indexVbo.unbind();

  // -----------------
  // |  Render func  |
  // -----------------
  std::function<void()> renderFunc = [&]() {
    BindLock<GLuint> lock1(vao), lock2(program);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, 0);
  };

  window.startRenderLoop(renderFunc);
  window.keyboard.onButtonPress -= &pressHandler;

  return 0;
}
