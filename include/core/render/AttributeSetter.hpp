#ifndef ATTRIBUTE_SETTER_HPP_
#define ATTRIBUTE_SETTER_HPP_
#include "Attribute.hpp"
#include "DIContainer.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/render/VBO.hpp"
#include <memory>

namespace core {
namespace render {
class IAttributeSetter {

public:
  virtual IAttributeSetter &addAttribute(std::shared_ptr<IAttribute> attribute,
                                         std::shared_ptr<GLbyte[]> memory,
                                         GLintptr memorySize) = 0;
  virtual IAttributeSetter &setAttributesTo(IVertexBufferObject &vbo) = 0;
};

class AttributeSetterItem;
class AttributeSetter : public IAttributeSetter {
  std::unique_ptr<AttributeSetterItem> setterDI_ = {nullptr};
  GLintptr totalMemorySize_ = 0;

public:
  IAttributeSetter &addAttribute(std::shared_ptr<IAttribute> attribute,
                                 std::shared_ptr<GLbyte[]> memory,
                                 GLintptr memorySize) override;
  IAttributeSetter &setAttributesTo(IVertexBufferObject &vbo) override;
};

class AttributeSetterItem : public deps::DI<IVertexBufferObject &, GLintptr &> {
public:
  AttributeSetterItem(std::shared_ptr<IAttribute> attribute,
                      std::shared_ptr<GLbyte[]> data, GLsizeiptr dataSize);
};
} // namespace render
} // namespace core
#endif // !ATTRIBUTE_SETTER_HPP_
