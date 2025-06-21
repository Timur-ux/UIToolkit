#ifndef DI_CONTAINER_HPP_
#define DI_CONTAINER_HPP_

#include <csignal>
#include <functional>
#include <memory>
namespace deps {

template <typename TArg>
class DI {
	std::unique_ptr<DI<TArg>> next_ = {nullptr};
	std::function<void(TArg)> handler_;
public:
	DI(std::function<void(TArg)> handler)
		: handler_(handler) {}

	DI & inject(std::unique_ptr<DI<TArg>> && dep) {
		dep->next_ = std::move(next_);
		next_ = std::move(dep);
		
		return *this;
	}

	DI & process(TArg arg) {
		handler_(arg);
		if(next_) 
			next_->process(arg);
	}
};
} // namespace deps

#endif // !DI_CONTAINER_HPP_
