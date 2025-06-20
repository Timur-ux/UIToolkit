#ifndef CORE_RENDER_ATTRIBUTE_HPP_
#define CORE_RENDER_ATTRIBUTE_HPP_

// -----------------------------
// |  Opengl vertex attribute  |
// -----------------------------
// -------------------------------------------------------------------------------------------
// |  It's is only info about attribute, raw data must be loaded from another source in VBO  |
// -------------------------------------------------------------------------------------------

#include "core/OpenGLHeaders.hpp"
#include "core/render/utils.hpp"
namespace core {
namespace render {
class IAttribute {
public:
  virtual GLuint location() const = 0;
  virtual GLenum type() const = 0;
  virtual GLuint size() const = 0;
  virtual GLuint stride() const = 0;
  virtual bool normalized() const = 0;

	virtual ~IAttribute() = default;
};

template <typename TData, size_t NComponents, bool Normalized>
class Attribute : public IAttribute {
  size_t location_;

public:
  Attribute(size_t location) : location_(location) {}
  GLuint location() const override { return location_; };
  constexpr GLenum type() const override { return type_mapper_t<TData>(); };
  constexpr GLuint size() const override { return NComponents; };
  constexpr GLuint stride() const override {
    return NComponents * sizeof(TData);
  }
  constexpr bool normalized() const override { return Normalized; }
};

// -----------------------
// |  common attributes  |
// -----------------------

template <size_t NComponents>
using attribute_f = Attribute<GLfloat, NComponents, false>;

template <size_t NComponents>
using attribute_i = Attribute<GLint, NComponents, false>;

template <size_t NComponents>
using attribute_b = Attribute<GLbyte, NComponents, false>;

} // namespace render
} // namespace core
#endif // !CORE_RENDER_ATTRIBUTE_HPP_
