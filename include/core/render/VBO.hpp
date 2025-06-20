#ifndef VBO_HPP_
#define VBO_HPP_

// -----------------------------------------------------------
// |  Vertex buffer object used to store vertex data in GPU  |
// -----------------------------------------------------------

#include "core/OpenGLHeaders.hpp"
#include "core/render/Attribute.hpp"

namespace core {
namespace render {

class IVertexBufferObject {
public:
  virtual GLuint id() const = 0;
  virtual IVertexBufferObject &bind() = 0;
	virtual IVertexBufferObject &setData(GLsizeiptr memorySize, const void * memory) = 0;
	virtual IVertexBufferObject &removeData() = 0;
	virtual IVertexBufferObject &setVertexAttribute(IAttribute &attrib, const void * offset) = 0;
	virtual IVertexBufferObject &copySubData(GLintptr offset, GLsizeiptr memorySize, const void * memory) = 0;

	virtual void * memoryMapToRead(GLintptr offset, GLsizeiptr length) = 0;
	virtual void * memoryMapToWrite(GLintptr offset, GLsizeiptr length) = 0;
	virtual IVertexBufferObject & memoryUnmap() = 0;

	virtual ~IVertexBufferObject() = default;
};

template <GLenum I>
concept VBOType = (I == GL_ARRAY_BUFFER) || (I == GL_ELEMENT_ARRAY_BUFFER);

template<GLenum I>
concept VBOUsage = (I == GL_STATIC_DRAW) || (I == GL_DYNAMIC_DRAW) || (I == GL_STATIC_READ) || (I == GL_DYNAMIC_READ);

template <GLenum BufferType, GLenum BufferUsage>
	requires VBOType<BufferType> && VBOUsage<BufferUsage>
class VertexBufferObject : public IVertexBufferObject {
private:
  GLuint id_;

	void *memoryMap(GLsizeiptr length, GLintptr offset, GLbitfield access) {
		bind();
		return glMapBufferRange(BufferType, offset, length, access);
	}
public:
  VertexBufferObject() {
    glGenBuffers(1, &id_);
  };


  VertexBufferObject(VertexBufferObject &) = delete;
  VertexBufferObject &operator=(VertexBufferObject &) = delete;

  VertexBufferObject(VertexBufferObject &&other) {
    id_ = other.id_;
    other.id_ = 0;
  }

  VertexBufferObject &operator=(VertexBufferObject &&other) {
    id_ = other.id_;
    other.id_ = 0;

    return *this;
  }

	IVertexBufferObject & bind() override {
		glBindBuffer(BufferType, id_);
		return *this;
	}

	IVertexBufferObject & setData(GLsizeiptr memorySize, const void *memory) override {
		bind();
		glBufferData(BufferType, memorySize, memory, BufferUsage);
		return *this;
	}

	IVertexBufferObject & removeData() override {
		bind();
		glBufferData(BufferType, 0, NULL, BufferUsage);
		return *this;
	}

	IVertexBufferObject & setVertexAttribute(IAttribute &attrib, const void *offset) override {
		bind();
		glEnableVertexAttribArray(attrib.location());
		glVertexAttribPointer(attrib.location(), attrib.size(), attrib.type(), attrib.normalized(), attrib.stride(), offset);

		return *this;
	}

	IVertexBufferObject & copySubData(GLintptr offset, GLsizeiptr memorySize, const void *memory) override {
		bind();
		glBufferSubData(BufferType, offset, memorySize, memory);

		return *this;
	}

	void * memoryMapToRead(GLintptr offset, GLsizeiptr length) override {
		bind();
		return memoryMap(length, offset, GL_MAP_READ_BIT);
	}

	void * memoryMapToWrite(GLintptr offset, GLsizeiptr length) override {
		bind();
		return memoryMap(length, offset, GL_MAP_WRITE_BIT);
	}

	IVertexBufferObject & memoryUnmap() override {
		bind();
		glUnmapBuffer(BufferType);
	}

	~VertexBufferObject() {
		bind();
		glDeleteBuffers(1, &id_);
	}

};

} // namespace render
} // namespace core
#endif // !VBO_HPP_
