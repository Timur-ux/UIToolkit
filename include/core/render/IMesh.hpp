#ifndef CORE_RENDER_MESH_HPP_
#define CORE_RENDER_MESH_HPP_
// --------------------
// |  Mesh interface  |
// --------------------

#include "IEntity.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/render/Attribute.hpp"
#include "core/render/AttributeSetter.hpp"
#include "core/render/IProgram.hpp"
#include "core/render/VAO.hpp"
#include "core/render/VBO.hpp"
#include "core/render/Vertex.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "core/render/Texture.hpp"

namespace core::render {
enum class RenderType {
	TRIANGLES = GL_TRIANGLES,
	TRIANGLES_FAN = GL_TRIANGLE_FAN,
	TRIANGLES_STRIP = GL_TRIANGLE_STRIP,
	POINTS = GL_POINTS,
	LINES = GL_LINES,
	LINES_STRIP = GL_LINE_STRIP,
	LINES_LOOP = GL_LINE_LOOP
};

class IMesh : public ui::IEntity {
public:
  virtual IEntity &render() = 0;
	virtual RenderType renderType() const = 0;
	virtual const IProgram & renderProgram() const = 0;
	virtual IMesh & setVertexes(const std::vector<Vertex> & vertexes, const std::vector<GLubyte> & indexes, std::string vertexAttribName = "coord") = 0;
	virtual IMesh & setColor(const std::vector<glm::vec3> & colors, std::string colorAttribName = "color") = 0;
	virtual IMesh & setTexture(std::unique_ptr<ITexture> texture, const std::vector<GLfloat> & textureCoords, std::string textureCoordsAttribName = "textureCoord") = 0;

	virtual IMesh & setCustomAttribute(IAttribute & attrib, const void * data, size_t dataSize) = 0;

	virtual ~IMesh() = default;
};

} // namespace core::render

#endif // !CORE_RENDER_MESH_HPP_
