#ifndef CORE_RENDER_MESH_HPP_
#define CORE_RENDER_MESH_HPP_
// --------------------
// |  Mesh interface  |
// --------------------

#include "IEntity.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/render/Attribute.hpp"
#include "core/render/IProgram.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "core/render/Texture.hpp"

namespace core::render {
enum class RenderType {
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	POINTS = GL_POINTS,
	LINES = GL_LINES,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP
};

class IMesh : public ui::IEntity {
public:
  virtual IEntity &render() = 0;
	virtual RenderType renderType() const = 0;
	virtual const IProgram & renderProgram() const = 0;
	virtual IMesh & setVertexes(const std::vector<glm::vec3> & vertexes, const std::vector<GLubyte> & indexes, std::string vertexAttribName = "coord") = 0;
	virtual IMesh & setColor(const std::vector<glm::vec3> & colors, std::string colorAttribName = "color") = 0;
	virtual IMesh & setTexture(std::unique_ptr<ITexture> texture, const std::vector<GLfloat> & textureCoords, std::string textureCoordsAttribName = "textureCoord") = 0;

	virtual IMesh & setCustomAttribute(std::shared_ptr<IAttribute> & attrib, std::shared_ptr<GLbyte[]> data, GLsizeiptr dataSize) = 0;

	virtual ~IMesh() = default;
};

} // namespace core::render

#endif // !CORE_RENDER_MESH_HPP_
