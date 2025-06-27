#include "core/render/MeshAttributeSetters.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/render/Attribute.hpp"
#include "core/render/Vertex.hpp"
#include <memory>
#include <vector>


void setRectangleVertexes(core::render::IMesh &mesh, size_t location) {
	std::vector<core::render::Vertex> vertexes{ 
		{-.5, -.5, .0},
		{.5, -.5, .0},
		{.5, .5, .0},
		{-.5, .5, 0}
	};
	std::vector<GLubyte> indexes{ 0, 1, 2, 3 };

	mesh.setVertexes(vertexes, indexes);
}

void setColor(core::render::IAttributeSetter & setter, glm::vec4 color, size_t nVertex, size_t location) {
	std::shared_ptr<core::render::Attribute<GLfloat, 4, true>> attribute{new core::render::Attribute<GLfloat, 4, true>{location}};
	
	glm::vec4 * memory = new glm::vec4[nVertex];
	for(size_t i = 0; i < nVertex; ++i) 
		memory[i] = color;
	size_t memorySize = sizeof(glm::vec4) * nVertex;

	std::shared_ptr<GLbyte[]> memPtr{(GLbyte*)memory};

	setter.addAttribute(attribute, memPtr, memorySize);
}
