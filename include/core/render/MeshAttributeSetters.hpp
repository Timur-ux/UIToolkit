#ifndef MESH_ATTRIBUTE_SETTERS_HPP_
#define MESH_ATTRIBUTE_SETTERS_HPP_

#include "core/render/AttributeSetter.hpp"
#include <glm/glm.hpp>

void setRectangleVertexes(core::render::IAttributeSetter & setter, size_t location);
void setColor(core::render::IAttributeSetter & setter, glm::vec4 color, size_t nVertex, size_t location);

#endif // !MESH_ATTRIBUTE_SETTERS_HPP_
