#include "core/render/Program.hpp"
#include "IBindable.hpp"
#include "core/OpenGLHeaders.hpp"
#include "core/render/IProgram.hpp"
#include "utils/error.hpp"
#include <fstream>
#include <memory>
#include <string>

using namespace core::render;

Program::Program(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open())
    utils::error() << "Can't open file [" << filename << "]";

  std::string line, text;
  std::getline(file, line);
  if (line != "// vertex")
    utils::error() << "Shader file: expected [// vertex] at the first line";

  while (std::getline(file, line) && line != "// fragment")
    text += line + '\n';

  if (!file)
    utils::error()
        << "Shader file: header of fragment shader [// fragment] not found";

  vertexShader_.init(text);
  text = "";
  while (std::getline(file, line))
    text += line + '\n';

  fragmentShader_.init(text);

  id_ = glCreateProgram();
	vertexShader_.linkTo(*this);
	fragmentShader_.linkTo(*this);
	glLinkProgram(id_);

	GLint linkStatus, logLength;
	glGetProgramiv(id_, GL_LINK_STATUS, &linkStatus);
	if(linkStatus == GL_TRUE) 
		return;
	
	glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &logLength);
	auto buffer = std::make_unique<char[]>(logLength);
	glGetProgramInfoLog(id_, logLength, NULL, buffer.get());

	utils::error() << "Linking program failed. Reason:" << std::endl << buffer;
}

Program::~Program() { glDeleteProgram(id_); }

void Program::linkShader(GLuint shaderId) {
	glAttachShader(id_, shaderId);
}


GLint Program::getUniformLocation(std::string name) {
	return glGetUniformLocation(id_, name.c_str());
}

IBindable & Program::bind() {
	glUseProgram(id_);

	return *this;
}

IBindable & Program::unbind(GLuint oldBind) {
	glUseProgram(oldBind);

	return *this;
}

void Program::setUniform(uniform_setter &setter) {
	bind();
	setter(id_);
	unbind();
}

