#include "IBindable.hpp"

BindLock::BindLock(IBindable &bind) : bind_(bind) { oldBind_ = bind_.getCurrentBind(); bind_.bind(); }

BindLock::~BindLock() {
	bind_.unbind(oldBind_);
}
