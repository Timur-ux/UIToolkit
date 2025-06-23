#ifndef CORE_RENDER_SHADER_HPP_
#define CORE_RENDER_SHADER_HPP_
#include "core/OpenGLHeaders.hpp"
#include "utils/error.hpp"
#include <fstream>
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
  virtual GLuint id() const = 0;
	virtual void init(std::string filename) = 0;

  virtual ~IShader() = default;
};

template <ShaderType TShader> class Shader : public IShader {
  GLuint id_;

public:
  Shader() : id_(glCreateShader(static_cast<GLuint>(type()))) {}
  ~Shader() { glDeleteShader(id_); }

  GLuint id() const override { return id_; }
  constexpr ShaderType type() const override { return TShader; }

	void init(std::string filename) override {
		std::ifstream file(filename);
		if(!file.is_open())
			utils::error() << "Can't open file by given filename [" << filename << "]";

		std::string line, text = "";
		while(std::getline(file, line)) 
			text += line + '\n';

		const char * addr = text.c_str();

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
};

} // namespace core::render
#endif // !CORE_RENDER_SHADER_HPP_
