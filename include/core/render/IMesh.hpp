#ifndef CORE_RENDER_MESH_HPP_
#define CORE_RENDER_MESH_HPP_
// --------------------
// |  Mesh interface  |
// --------------------

#include "IEntity.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/render/AttributeSetter.hpp"
#include "core/render/VBO.hpp"
#include "core/render/VAO.hpp"
#include "core/render/Vertex.hpp"
#include <cstddef>

namespace core::render {
class IMesh : public ui::IEntity {
public:
	virtual size_t nVertex () = 0;
	virtual IVertex * vertexes () = 0;

	virtual IEntity& render() = 0;
};


class MeshBase : public IMesh {
	VertexBufferObject<GL_ARRAY_BUFFER, GL_STATIC_DRAW> attributeVbo_;
	VertexBufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_READ> indexes_;
	VertexArrayObject vao_;
	AttributeSetter attributeSetter_;

public:

};
} // namespace core::render


#endif // !CORE_RENDER_MESH_HPP_
