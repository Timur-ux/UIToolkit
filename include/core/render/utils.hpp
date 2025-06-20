#ifndef CORE_RENDER_UTILS_HPP_
#define CORE_RENDER_UTILS_HPP_
#include "core/OpenGLHeaders.hpp"

template <typename T> struct type_mapper {};

template <typename T> constexpr GLenum type_mapper_t() {
  return type_mapper<T>::type;
}

template <> struct type_mapper<GLfloat> {
  static constexpr GLenum type = GL_FLOAT;
};

template <> struct type_mapper<GLdouble> {
  static constexpr GLenum type = GL_DOUBLE;
};

template <> struct type_mapper<GLbyte> {
  static constexpr GLenum type = GL_BYTE;
};

template <> struct type_mapper<GLint> {
  static constexpr GLenum type = GL_INT;
};
template <> struct type_mapper<GLuint> {
  static constexpr GLenum type = GL_UNSIGNED_INT;
};

template <> struct type_mapper<GLubyte> {
  static constexpr GLenum type = GL_UNSIGNED_BYTE;
};
template <> struct type_mapper<GLshort> {
  static constexpr GLenum type = GL_SHORT;
};

template <> struct type_mapper<GLushort> {
  static constexpr GLenum type = GL_UNSIGNED_SHORT;
};
#endif // !CORE_RENDER_UTILS_HPP_
