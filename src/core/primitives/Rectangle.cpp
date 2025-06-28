#include "core/primitives/Rectangle.hpp"
#include <stdexcept>

namespace core::primitives {
Rectangle::Rectangle(std::shared_ptr<render::IProgram> program) 
	: parent_t(program) {
		std::vector<glm::vec3> coords{
			{-1, -1, 0},
			{1, -1, 0},
			{1, 1, 0},
			{-1, 1, 0}
		};
	
		std::vector<GLubyte> indexes{0, 1, 2, 3};

		setVertexes(coords, indexes);
	}

Rectangle::Rectangle(std::shared_ptr<render::IProgram> program, glm::vec3 color)
:  Rectangle(program)  {
	std::vector<glm::vec3> colors(nVertexes(), color);
	setColor(colors);
}

Rectangle::Rectangle(std::shared_ptr<render::IProgram> program, std::shared_ptr<render::ITexture> texture)
: Rectangle(program) {
	throw std::runtime_error("Textured rectangle not supported yet");
}


} // namespace core::primitives
