#ifndef UI_MESH_BASE_HPP_
#define UI_MESH_BASE_HPP_

#include "IBindable.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/render/AttributeSetter.hpp"
#include "core/render/IMesh.hpp"
#include "core/render/IProgram.hpp"
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
  std::shared_ptr<IProgram> renderProgram_;

  AttributeSetter attributeSetter_;
  size_t nVertexes_ = 0;

  void initRegistredAttributes() {
    BindLock<GLuint> lock(vao_);
    attributeSetter_.setAttributesTo(attribVbo_);
  }

  bool isInitialized = false;

public:
  MeshBase(std::shared_ptr<IProgram> renderProgram)
      : renderProgram_(renderProgram) {
    {
      BindLock<GLuint> lock{vao_};
      attribVbo_.bind(), indexVbo_.bind();
    }
    attribVbo_.unbind(), indexVbo_.bind();
  }; // namespace core::render

  IEntity &render() override {
    if (!isInitialized) {
      initRegistredAttributes();
      isInitialized = true;
    }

    BindLock<GLuint> lock1(vao_), lock2(*renderProgram_);
    glDrawElements(GLenum(TRender), GLsizei(nVertexes_), GL_UNSIGNED_BYTE, 0);

    return *this;
  }

  constexpr RenderType renderType() const override { return TRender; }
  const IProgram &renderProgram() const override { return *renderProgram_; }

  IMesh &setVertexes(const std::vector<glm::vec3> &vertexes,
                     const std::vector<GLubyte> &indexes,
                     std::string vertexAttribName = "coord") override {
    isInitialized = false;
    GLint location = renderProgram_->getAttribLocation(vertexAttribName);

    if (vertexes.size() != indexes.size())
      throw std::invalid_argument(
          "Vertexes and it's indexes must have the same size");
    if (location < 0)
      throw std::invalid_argument(utils::strfast()
                                  << "Vertex attribute with given name ["
                                  << vertexAttribName << "] not found");
    nVertexes_ = vertexes.size();

    GLsizeiptr memorySize = sizeof(glm::vec3) * nVertexes_;
    auto memory = std::make_shared<GLbyte[]>(memorySize);
    memcpy(memory.get(), (const void *)vertexes.data(), memorySize);
    auto attribData = std::make_shared<Attribute<GLfloat, 3, false>>(location);

    attributeSetter_.addAttribute(AttributeSetterData{
        .attribute = attribData, .data = memory, .dataSize = memorySize});
    indexVbo_.setData(sizeof(GLubyte) * indexes.size(), indexes.data());
    return *this;
  }

  IMesh &setColor(const std::vector<glm::vec3> &colors,
                  std::string colorAttribName = "color") override {
    isInitialized = false;
    GLint location = renderProgram_->getAttribLocation(colorAttribName);

    if (colors.size() != nVertexes_)
      throw std::invalid_argument(
          utils::strfast()
          << "Color values quantity must match quantity of vertexes. Vertexes: "
          << nVertexes_ << "; Color quantity: " << colors.size());
    if (location < 0)
      throw std::invalid_argument(utils::strfast()
                                  << "Vertex attribute with given name ["
                                  << colorAttribName << "] not found");

    GLsizeiptr memorySize = sizeof(glm::vec3) * nVertexes_;
    auto memory = std::make_shared<GLbyte[]>(memorySize);
    memcpy(memory.get(), (const void *)colors.data(), memorySize);
    auto attribData = std::make_shared<Attribute<GLfloat, 3, false>>(location);

    attributeSetter_.addAttribute(AttributeSetterData{
        .attribute = attribData, .data = memory, .dataSize = memorySize});
    return *this;
  }

  IMesh &
  setTexture(std::unique_ptr<ITexture> texture,
             const std::vector<GLfloat> &textureCoords,
             std::string textureCoordsAttribName = "textureCoord") override {

    isInitialized = false;
    throw std::runtime_error("Texture support not realized yet");
    return *this;
  }

  IMesh &setCustomAttribute(std::shared_ptr<IAttribute> &attrib,
                            std::shared_ptr<GLbyte[]> data,
                            GLsizeiptr dataSize) override {
    isInitialized = false;
    if (dataSize / attrib->stride() != nVertexes_)
      throw std::invalid_argument(
          utils::strfast()
          << "Attrib must be set for all vertexes, i.e. size of data must be "
             "equal attrib.stride * nVertexes. Given nVertexes * stride: "
          << nVertexes_ * attrib->stride() << "; data size: " << dataSize);
    attributeSetter_.addAttribute(
        {.attribute = attrib, .data = data, .dataSize = dataSize});

    return *this;
  }

  size_t nVertexes() const { return nVertexes_; }
};
} // namespace core::render

#endif // !UI_MESH_BASE_HPP_
