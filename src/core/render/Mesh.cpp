#include "core/OpenGLHeaders.hpp"
#include "core/render/IMesh.hpp"

using namespace core::render;
MeshBase::MeshBase(std::shared_ptr<IProgram> program, GLenum renderType) : program_(program), renderType_(renderType) {}

const glm::mat4 &MeshBase::model() const { return model_; }

IAttributeSetter &MeshBase::attributes() {
  initialized_ = false;
  return attributeSetter_;
}
IAttributeSetter &MeshBase::vertexIndexesSetter() {
  initialized_ = false;
  return indexesSetter_;
}

void MeshBase::init() {
  vao_.bind();
  if (!initialized_) {
    attributeSetter_.setAttributesTo(attributeVbo_);
    indexesSetter_.setAttributesTo(indexesVbo_);
    initialized_ = true;
  }
  attributeVbo_.bind();
  indexesVbo_.bind();
  vao_.unbind();
}

ui::IEntity &MeshBase::render() {
  if (!initialized_)
    init();

	program_->bind();
  vao_.bind();
	glDrawElements(renderType_, 4, GL_UNSIGNED_BYTE, 0);
	program_->unbind(0);
  vao_.unbind();
  return *this;
}
