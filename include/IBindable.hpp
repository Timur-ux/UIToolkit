#ifndef IBINDABLE_HPP_
#define IBINDABLE_HPP_

#include "core/OpenGLHeaders.hpp"
class IBindable;

/**
 * @brief RAII lock
 */
class BindLock {
	GLuint oldBind_ = 0;
	IBindable & bind_;
public:
	BindLock(IBindable& bind);
	~BindLock();
};

class IBindable {
public:
	virtual IBindable& bind () = 0;
	virtual IBindable& unbind (GLuint oldLock) = 0;
	virtual GLuint getCurrentBind() = 0;
};

#endif // !IBINDABLE_HPP_
