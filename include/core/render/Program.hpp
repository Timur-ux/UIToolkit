#ifndef CORE_RENDER_PROGRAM_HPP_
#define CORE_RENDER_PROGRAM_HPP_
#include "IBindable.hpp"
#include "core/render/IProgram.hpp"
#include "core/render/Shader.hpp"
#include <string>

namespace core::render {
class Program : public IProgram {
	GLuint id_;
	Shader<ShaderType::VERTEX> vertexShader_;
	Shader<ShaderType::FRAGMENT> fragmentShader_;
public:
	Program(std::string fileName);
	~Program();

	IBindable & bind() override;
	IBindable & unbind(GLuint oldBind = 0) override;
	void setUniform(uniform_setter &) override;
	void linkShader(GLuint shaderId) override;
	GLint getUniformLocation(std::string name) override;
};

} // namespace core::render
#endif // !CORE_RENDER_PROGRAM_HPP_
