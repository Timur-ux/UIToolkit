#ifndef CORE_RENDER_TEXTURE_HPP_
#define CORE_RENDER_TEXTURE_HPP_
#include "DIContainer.hpp"
#include "IBindable.hpp"
#include "core/OpenGLHeaders.hpp"
#include <memory>

namespace core::render {
template <GLenum I>
concept TextureType = (I == GL_TEXTURE_1D) || (I == GL_TEXTURE_2D) ||
                      (I == GL_TEXTURE_3D) || (I == GL_TEXTURE_CUBE_MAP);
template <GLenum I>
concept ImageType = (I == GL_RGB) || (I == GL_RGBA) || (I == GL_ALPHA);

class ITexture : public IBindable {
public:
  virtual bool isImageLoaded() const = 0;
  virtual ITexture &loadImage(const GLubyte *data, GLsizei width,
                              GLsizei height, GLsizei depth) = 0;

  virtual GLenum textureType() const = 0;
  virtual GLenum imageType() const = 0;
  virtual size_t textureBlock() const = 0;
};

using preinit_param_t = deps::DI<>;
using postinit_param_t = deps::DI<ITexture &>;

template <GLenum TTexture, GLenum TImage, size_t TBlock = 0>
  requires TextureType<TTexture> && ImageType<TImage> && (TBlock < 16)
class Texture : public ITexture {
  using class_type = Texture<TTexture, TImage, TBlock>;

  GLuint id_;
  bool isImageLoaded_ = false;

public:
  Texture(preinit_param_t &preinitParams, postinit_param_t &postinitParams) {
    preinitParams.process();
    glGenTextures(1, &id_);
    bind();
    textureParams(*this);
  }

  Texture(class_type &other) = delete;
  Texture &operator=(class_type &other) = delete;

  Texture(class_type &&other) {
    id_ = other.id_;
    other.id_ = 0;
  }

  Texture &operator=(class_type &&other) {
    id_ = other.id_;
    other.id_ = 0;

    return *this;
  }

  constexpr GLenum textureType() const override { return TTexture; }
  constexpr GLenum imageType() const override { return TImage; }
  constexpr size_t textureBlock() const override { return TBlock; }

  bool isImageLoaded() const override { return isImageLoaded_; }

  IBindable &bind() override {
    glActiveTexture(TBlock);
    glBindTexture(TTexture, id_);

    return *this;
  }

  IBindable &unbind(GLuint oldBind = 0) override {
    glBindTexture(TTexture, oldBind);

    return *this;
  }

  ITexture &loadImage(const GLubyte *data, GLsizei width, GLsizei height = 0,
                      GLsizei depth = 0) override {
    switch (TTexture) {
    case GL_TEXTURE_1D:
      glTexImage1D(TTexture, 0, TImage, width, 0, TTexture, GL_UNSIGNED_BYTE,
                   data);
    case GL_TEXTURE_2D:
      glTexImage2D(TTexture, 0, TImage, width, height, 0, TImage,
                   GL_UNSIGNED_BYTE, data);
    case GL_TEXTURE_3D:
      glTexImage3D(TTexture, 0, TImage, width, height, depth, 0, TImage,
                   GL_UNSIGNED_BYTE, data);
    }

    isImageLoaded_ = true;
    return *this;
  }
};

inline const preinit_param_t basePreinitParams{
    []() { glPixelStorei(GL_UNPACK_ALIGNMENT, 1); }};
inline const postinit_param_t basePostinitParams =
    std::move(postinit_param_t{[](ITexture &tex) {
      glTexParameteri(tex.textureType(), GL_TEXTURE_WRAP_S, GL_REPEAT);
      if (tex.textureType() > GL_TEXTURE_1D)
        glTexParameteri(tex.textureType(), GL_TEXTURE_WRAP_R, GL_REPEAT);
      if (tex.textureType() > GL_TEXTURE_2D)
        glTexParameteri(tex.textureType(), GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(tex.textureType(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(tex.textureType(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }});

} // namespace core::render
#endif // !CORE_RENDER_TEXTURE_HPP_
