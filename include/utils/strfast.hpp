#ifndef STRFAST_HPP_
#define STRFAST_HPP_

#include <sstream>
namespace utils {
struct strfast : std::stringstream {
	operator std::string() const {
		return str();
	}
};
} // namespace utils

#endif // !STRFAST_HPP_
