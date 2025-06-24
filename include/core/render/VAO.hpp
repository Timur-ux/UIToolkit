#ifndef CORE_RENDER_HPP_
#define CORE_RENDER_HPP_
#include "IBindable.hpp"
#include "core/OpenGLHeaders.hpp"
#include <functional>
namespace core {
namespace render {

class IVertexArrayObject : public IBindable<GLuint> {
public:
  virtual ~IVertexArrayObject() = default;
};

class VertexArrayObject : public IVertexArrayObject {
  GLuint id_ = 0;

public:
  VertexArrayObject() { glGenVertexArrays(1, &id_); }

  VertexArrayObject(VertexArrayObject &) = delete;
  VertexArrayObject &operator=(VertexArrayObject &) = delete;

  VertexArrayObject(VertexArrayObject &&other) {
    id_ = other.id_;
    other.id_ = 0;
  };

  VertexArrayObject &operator=(VertexArrayObject &&other) {
    id_ = other.id_;
    other.id_ = 0;

    return *this;
  }

	~VertexArrayObject() {
		glDeleteVertexArrays(1, &id_);
		id_ = 0;
	}


  IBindable &bind() override {
    glBindVertexArray(id_);

    return *this;
  }

	IBindable & unbind(GLuint oldBind = 0) override {
    glBindVertexArray(oldBind);

    return *this;
	}
	GLuint getCurrentBind() override {
		GLint result;
		glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &result);
		return result;
	}
};

} // namespace render
} // namespace core
#endif // !CORE_RENDER_HPP_
