#ifndef CORE_RENDER_SHADER_HPP_
#define CORE_RENDER_SHADER_HPP_
#include "core/OpenGLHeaders.hpp"
#include "core/render/IProgram.hpp"
#include "utils/error.hpp"
#include <memory>
#include <string>
namespace core::render {

enum class ShaderType {
  VERTEX = GL_VERTEX_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER,
};

class IShader {
public:
  virtual ShaderType type() const = 0;
	virtual void init(std::string shaderText) = 0;
	virtual void linkTo(IProgram & program) = 0;

  virtual ~IShader() = default;
};

template <ShaderType TShader> class Shader : public IShader {
  GLuint id_;

public:
  Shader() : id_(glCreateShader(static_cast<GLuint>(type()))) {}
  ~Shader() { glDeleteShader(id_); }

  constexpr ShaderType type() const override { return TShader; }

	void init(std::string shaderText) override {
		const char * addr = shaderText.c_str();

		glShaderSource(id_, 1, &addr, NULL);
		glCompileShader(id_);

		GLint compileStatus, logLength;

		glGetShaderiv(id_, GL_COMPILE_STATUS, &compileStatus);
		if(compileStatus == GL_TRUE) 
			return;
		
		glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &logLength);
		auto buffer = std::make_unique<char[]>(logLength);

		glGetShaderInfoLog(id_, logLength, NULL, buffer.get());
		utils::error() << "Shader compilation failed. Reason: " << std::endl << buffer;
	}

	void linkTo(IProgram &program) override {
		program.linkShader(id_);
	}
};

} // namespace core::render
#endif // !CORE_RENDER_SHADER_HPP_
