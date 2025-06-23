#include "core/render/IMesh.hpp"

using namespace core::render;

const glm::mat4 &MeshBase::model() const { return model_; }

IAttributeSetter &MeshBase::attributes() {
    initialized_ = false;
    return attributeSetter_;
}
IAttributeSetter & MeshBase::vertexIndexesSetter() {
	initialized_ = false;
	return indexesSetter_;
}

void MeshBase::init() {
	vao_.bind();
	if(!initialized_) {
		attributeSetter_.setAttributesTo(attributeVbo_);
		indexesSetter_.setAttributesTo(indexesVbo_);
		initialized_ = true;
	}
	attributeVbo_.bind();
	indexesVbo_.bind();
	vao_.unbind();
}


ui::IEntity & MeshBase::render() {
	if(!initialized_) init(); 
		
	vao_.bind();
	// ----------------------------
	// |  TODO: add render logic  |
	// ----------------------------
	vao_.unbind();
	return *this;
}
