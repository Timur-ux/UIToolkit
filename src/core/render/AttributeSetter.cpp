#include "core/render/AttributeSetter.hpp"
#include <memory>

using namespace core::render;

IAttributeSetter &
AttributeSetter::addAttribute(std::shared_ptr<IAttribute> attribute,
                              std::shared_ptr<void> memory,
                              GLintptr memorySize) {
  if (setterDI_)
    setterDI_->inject(std::move(
        std::make_unique<AttributeSetterItem>(attribute, memory, memorySize)));
  setterDI_ =
      std::make_unique<AttributeSetterItem>(attribute, memory, memorySize);

  totalMemorySize_ += memorySize;

  return *this;
}

IAttributeSetter &AttributeSetter::setAttributesTo(IVertexBufferObject &vbo) {
  vbo.setData(totalMemorySize_, NULL);
  GLsizeiptr offset = 0;
  setterDI_->process(vbo, offset);
  return *this;
}

AttributeSetterItem::AttributeSetterItem(std::shared_ptr<IAttribute> attribute,
                                         std::shared_ptr<void> data,
                                         GLsizeiptr dataSize)

    : deps::DI<IVertexBufferObject &, GLintptr &>(
          [attribute, data, dataSize](IVertexBufferObject &vbo,
                                      GLintptr &offset) {
            vbo.copySubData(offset, dataSize, data.get());
            vbo.setVertexAttribute(*attribute, (const void *)offset);
            offset += dataSize;
          }) {}
