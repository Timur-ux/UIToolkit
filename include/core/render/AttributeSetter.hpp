#ifndef ATTRIBUTE_SETTER_HPP_
#define ATTRIBUTE_SETTER_HPP_
#include "Attribute.hpp"
#include "DIContainer.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/render/VBO.hpp"
#include <map>
#include <memory>

namespace core {
namespace render {
struct AttributeSetterData {
  std::shared_ptr<IAttribute> attribute;
  std::shared_ptr<GLbyte[]> data;
  GLsizeiptr dataSize;
};

class IAttributeSetter {

public:
  virtual IAttributeSetter &addAttribute(AttributeSetterData data) = 0;
  virtual IAttributeSetter &setAttributesTo(IVertexBufferObject &vbo) = 0;
};

class AttributeSetterItem;

class AttributeSetter : public IAttributeSetter {
  std::unique_ptr<AttributeSetterItem> setterDI_ = {nullptr};
  GLintptr totalMemorySize_ = 0;
  std::map<GLuint, AttributeSetterItem *> existingAttributes_;

public:
  IAttributeSetter &addAttribute(AttributeSetterData data) override;
  IAttributeSetter &setAttributesTo(IVertexBufferObject &vbo) override;
};

class AttributeSetterItem : public deps::DI<IVertexBufferObject &, GLintptr &> {
public:
  AttributeSetterItem(AttributeSetterData data);

  void replaceAttributeTo(AttributeSetterData data);
};
} // namespace render
} // namespace core
#endif // !ATTRIBUTE_SETTER_HPP_
