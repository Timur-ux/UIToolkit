#ifndef CORE_RENDER_IPROGRAM_HPP_
#define CORE_RENDER_IPROGRAM_HPP_
// -----------------------------------
// |  Render program implementation  |
// -----------------------------------

#include "IBindable.hpp"
#include "core/OpenGLHeaders.hpp"
#include <functional>
#include <string>
namespace core::render {
using uniform_setter = std::function<void(GLuint programId)>;

class IProgram : public IBindable {
public:
	virtual void setUniform(uniform_setter &) = 0;
	virtual void linkShader(GLuint shaderId) = 0;
	virtual GLint getUniformLocation(std::string name) = 0; 

	virtual ~IProgram() = default;
};
} // namespace core::render


#endif // !CORE_RENDER_IPROGRAM_HPP_
