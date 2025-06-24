#ifndef IBINDABLE_HPP_
#define IBINDABLE_HPP_

#include "core/OpenGLHeaders.hpp"
template <typename TBind> class IBindable;

/**
 * @brief RAII lock
 */
template <typename TBind> class BindLock {
  GLuint oldBind_ = 0;
  IBindable<TBind> &bind_;

public:
  BindLock(IBindable<TBind> &bind) : bind_(bind) {
    oldBind_ = bind_.getCurrentBind();
    bind_.bind();
  }
  ~BindLock() { bind_.unbind(oldBind_); }
};

template <typename TBind> class IBindable {
public:
  virtual IBindable &bind() = 0;
  virtual IBindable &unbind(TBind oldLock) = 0;
  virtual TBind getCurrentBind() = 0;
};

#endif // !IBINDABLE_HPP_
