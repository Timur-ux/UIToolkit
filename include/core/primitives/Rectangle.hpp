#ifndef CORE_PRIMITIVES_RECTANGLE_HPP_
#define CORE_PRIMITIVES_RECTANGLE_HPP_
#include "core/MeshBase.hpp"
#include "core/render/IMesh.hpp"
#include "core/render/IProgram.hpp"
#include "core/render/Texture.hpp"
namespace core::primitives {
class Rectangle : public render::MeshBase<render::RenderType::TRIANGLE_FAN> {
	using parent_t = render::MeshBase<render::RenderType::TRIANGLE_FAN>;
	Rectangle(std::shared_ptr<render::IProgram> program);
	public:
		Rectangle(std::shared_ptr<render::IProgram> program, glm::vec3 color);
		Rectangle(std::shared_ptr<render::IProgram> program, std::shared_ptr<render::ITexture> texture);
};
} // namespace core::primitives
#endif // !CORE_PRIMITIVES_RECTANGLE_HPP_
