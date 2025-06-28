#ifndef UI_MESH_BASE_HPP_
#define UI_MESH_BASE_HPP_

#include "IBindable.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/render/AttributeSetter.hpp"
#include "core/render/IMesh.hpp"
#include "core/render/Program.hpp"
#include "core/render/VAO.hpp"
#include "core/render/VBO.hpp"
#include "utils/strfast.hpp"
#include <cassert>
#include <cstring>
#include <memory>
#include <stdexcept>

namespace core::render {
template <RenderType TRender> class MeshBase : public IMesh {
  VertexArrayObject vao_;
  VertexBufferObject<GL_ARRAY_BUFFER, GL_STATIC_DRAW> attribVbo_;
  VertexBufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_READ> indexVbo_;
  Program renderProgram_;

  AttributeSetter attributeSetter_;
  size_t nVertexes_ = 0;

public:
  MeshBase() {
    {
      BindLock<GLuint> lock{vao_};
      attribVbo_.bind(), indexVbo_.bind();
    }
    attribVbo_.unbind(), indexVbo_.bind();
  }; // namespace core::render

  IEntity &render() override {}

  constexpr RenderType renderType() const override { return TRender; }
  const IProgram &renderProgram() const override { return renderProgram_; }

  IMesh &setVertexes(const std::vector<Vertex> &vertexes,
                     const std::vector<GLubyte> &indexes,
                     std::string vertexAttribName = "coord") override {
    GLint location = renderProgram_.getAttribLocation(vertexAttribName);

    if (vertexes.size() != indexes.size())
      throw std::invalid_argument(
          "Vertexes and it's indexes must have the same size");
    if (location < 0)
      throw std::invalid_argument(utils::strfast()
                                  << "Vertex attribute with given name ["
                                  << vertexAttribName << "] not found");
		nVertexes_ = vertexes.size();

		GLsizeiptr memorySize = sizeof(Vertex) * nVertexes_;
		auto memory = std::make_shared<GLbyte[]>(memorySize);
		memcpy(memory.get(), (const void*)vertexes.data(), memorySize);
		auto attribData = std::make_shared<Attribute<GLfloat, 3, false>>(location);

		attributeSetter_.addAttribute(AttributeSetterData{.attribute = attribData, .data = memory, .dataSize = memorySize});
		indexVbo_.setData(sizeof(GLubyte) * indexes.size(), indexes.data());
  }
};
} // namespace core::render

#endif // !UI_MESH_BASE_HPP_
