#include "core/render/AttributeSetter.hpp"
#include <memory>

using namespace core::render;

IAttributeSetter &AttributeSetter::addAttribute(AttributeSetterData data) {

  if (existingAttributes_.contains(data.attribute->location())) {
    existingAttributes_[data.attribute->location()]->replaceAttributeTo(data);
    return *this;
  }

  auto attributeSetterItem = std::make_unique<AttributeSetterItem>(data);
  existingAttributes_[data.attribute->location()] = attributeSetterItem.get();
	if (setterDI_)
    setterDI_->inject(std::move(attributeSetterItem));
	else
		setterDI_ = std::move(attributeSetterItem);

	totalMemorySize_ += data.dataSize;

  return *this;
}

IAttributeSetter &AttributeSetter::setAttributesTo(IVertexBufferObject &vbo) {
  vbo.setData(totalMemorySize_, NULL);
  GLsizeiptr offset = 0;
  setterDI_->process(vbo, offset);
  return *this;
}

AttributeSetterItem::AttributeSetterItem(AttributeSetterData data)

    : deps::DI<IVertexBufferObject &, GLintptr &>(
          [data](IVertexBufferObject &vbo, GLintptr &offset) {
            vbo.copySubData(offset, data.dataSize, data.data.get());
            vbo.setVertexAttribute(*data.attribute, (const void *)offset);
            offset += data.dataSize;
          }) {}

void AttributeSetterItem::replaceAttributeTo(AttributeSetterData data) {
  handler_ = [data](IVertexBufferObject &vbo, GLintptr &offset) {
    vbo.copySubData(offset, data.dataSize, data.data.get());
    vbo.setVertexAttribute(*data.attribute, (const void *)offset);
    offset += data.dataSize;
  };
}
