#include "core/OpenGLHeaders.hpp"
#include "core/render/Attribute.hpp"
#include "core/render/IMesh.hpp"
#include "core/render/Vertex.hpp"
#include <cstring>
#include <memory>
#include <stdlib.h>

using namespace core::render;
MeshBase::MeshBase(std::shared_ptr<IProgram> program, GLenum renderType) : program_(program), renderType_(renderType) {}

const glm::mat4 &MeshBase::model() const { return model_; }

IAttributeSetter &MeshBase::attributes() {
  initialized_ = false;
  return attributeSetter_;
}

IMesh & MeshBase::setVertexes(const std::vector<Vertex> & vertexes, const std::vector<GLubyte> & indexes, size_t vertexesLocation) {
	size_t vertexesMemorySize = vertexes.size() * sizeof(Vertex);
	std::shared_ptr<GLbyte[]> vertexesMemory = std::make_shared<GLbyte[]>(vertexesMemorySize);
	memcpy(vertexesMemory.get(), (const void*)vertexes.data(), vertexesMemorySize);
	attributeSetter_.addAttribute(std::make_shared<Attribute<GLfloat, 3, true>>(0), vertexesMemory, vertexesMemorySize);

	size_t indexesMemorySize = indexes.size() * sizeof(GLubyte);
	std::shared_ptr<GLbyte[]> indexesMemory = std::make_shared<GLbyte[]>(indexesMemorySize);
	memcpy(indexesMemory.get(), (const void*)indexes.data(), vertexesMemorySize);
	attributeSetter_.addAttribute(std::make_shared<Attribute<GLubyte, 1, true>>(0), indexesMemory, indexesMemorySize);

	return *this;
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
