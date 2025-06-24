#ifndef CORE_RENDER_MESH_HPP_
#define CORE_RENDER_MESH_HPP_
// --------------------
// |  Mesh interface  |
// --------------------

#include "IEntity.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/render/AttributeSetter.hpp"
#include "core/render/IProgram.hpp"
#include "core/render/VAO.hpp"
#include "core/render/VBO.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/glm.hpp>
#include <memory>

namespace core::render {
class IMesh : public ui::IEntity {
public:
  virtual const glm::mat4 &model() const = 0;
  virtual IEntity &render() = 0;
  virtual IAttributeSetter &attributes() = 0;
	virtual IAttributeSetter &vertexIndexesSetter() = 0;
};

class MeshBase : public IMesh {
  VertexBufferObject<GL_ARRAY_BUFFER, GL_STATIC_DRAW> attributeVbo_;
  VertexBufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_READ> indexesVbo_;
  VertexArrayObject vao_;
  AttributeSetter attributeSetter_;
  AttributeSetter indexesSetter_;
  glm::mat4 model_ = {1};

  bool initialized_ = false;
	void init();
	std::shared_ptr<IProgram> program_;
	GLenum renderType_;

public:
	MeshBase(std::shared_ptr<IProgram>, GLenum renderType = GL_TRIANGLE_FAN);
  const glm::mat4 &model() const override;
	IAttributeSetter &attributes() override;
	IAttributeSetter & vertexIndexesSetter() override;
	IEntity & render() override;
};
} // namespace core::render

#endif // !CORE_RENDER_MESH_HPP_
