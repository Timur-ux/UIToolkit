#ifndef CORE_RENDER_HPP_
#define CORE_RENDER_HPP_
#include "core/OpenGLHeaders.hpp"
#include <functional>
namespace core {
namespace render {

class IVertexArrayObject {
public:
  virtual GLuint id() const = 0;
  virtual IVertexArrayObject &bind() = 0;
  virtual IVertexArrayObject &unbind() = 0;

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

  GLuint id() const override { return id_; }

  IVertexArrayObject &bind() override {
    glBindVertexArray(id_);

    return *this;
  }

	IVertexArrayObject & unbind() override {
    glBindVertexArray(0);

    return *this;
	}
};

} // namespace render
} // namespace core
#endif // !CORE_RENDER_HPP_
