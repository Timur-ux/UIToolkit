#ifndef EVENT_HPP_
#define EVENT_HPP_
/*
 * Event: interface and base class
 * Event handler: only interface, realization is user responsibility
 */

#include <iterator>
#include <list>
#include <memory>
#include <utility>
namespace event {
template <typename ...Args>
class IEventHandler;

template <typename ...Args>
class IEvent {
public:
	using handler_type = std::shared_ptr<IEventHandler<Args...>>;
	virtual IEvent<Args...>& operator+=(handler_type) = 0;
	virtual IEvent<Args...>& operator-=(handler_type) = 0;
};

template <typename ...Args>
class IEventHandler {
public:
	virtual void operator()(Args... args) = 0;
};

template <typename ...Args>
class Event : public IEvent<Args...>{
private:
	using handler_type = typename IEvent<Args...>::handler_type;
	using hadlers_type = std::list<handler_type>;

	hadlers_type handlers_;
public:
	IEvent<Args...> & operator+=(handler_type handler) override {
		handlers_.push_back(handler);
		return *this;
	}

	IEvent<Args...> & operator-=(handler_type handler) override {
		auto it = std::begin(handlers_);
		for (; it != std::end(handlers_) && (*it != handler); ++it) { }
		if(it != std::end(handlers_)) 
			handlers_.erase(it);
		
		return *this;
	}

	void invoke(Args... args) {
		for(auto& handler : handlers_) 
			(*handler)(std::forward(args...));
	}
};

} // namespace event
#endif // !EVENT_HPP_
