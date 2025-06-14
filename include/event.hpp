#ifndef EVENT_HPP_
#define EVENT_HPP_
/*
 * Event: interface and base class
 * Event handler: only interface, realization is user responsibility
 */

#include <functional>
#include <iterator>
#include <list>
namespace event {
template <typename... Args> class IEventHandler;

template <typename... Args> class IEvent {
public:
  using handler_type = IEventHandler<Args...> *;
  virtual IEvent<Args...> &operator+=(handler_type) = 0;
  virtual IEvent<Args...> &operator-=(handler_type) = 0;
};

template <typename... Args> class IEventHandler {
public:
  virtual void operator()(Args... args) = 0;
	virtual ~IEventHandler() = default;
};



/**
 * @brief Helper class used to create event handlers from lambdas
 */
template <typename... Args>
class LambdaHandler : public IEventHandler<Args...> {
  std::function<void(Args...)> f_;

public:
  LambdaHandler(const std::function<void(Args...)> &f) : f_(f) {}
  void operator()(Args... args) override { f_(args...); }
};

template <typename... Args> class Event : public IEvent<Args...> {
private:
  using handler_type = typename IEvent<Args...>::handler_type;
  using hadlers_type = std::list<handler_type>;

  hadlers_type handlers_;

public:
  IEvent<Args...> &operator+=(handler_type handler) override {
    handlers_.push_back(handler);
    return *this;
  }

  IEvent<Args...> &operator-=(handler_type handler) override {
    auto it = std::begin(handlers_);
    for (; it != std::end(handlers_) && (*it != handler); ++it) {
    }
    if (it != std::end(handlers_))
      handlers_.erase(it);

    return *this;
  }

  void invoke(Args... args) {
    for (auto &handler : handlers_)
      (*handler)(args...);
  }
};

} // namespace event
#endif // !EVENT_HPP_
