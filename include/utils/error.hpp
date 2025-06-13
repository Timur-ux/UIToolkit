#ifndef UTILS_ERROR_HPP_
#define UTILS_ERROR_HPP_

/*
 * Simply print error message to cerr thread, terminates glfw and exiting program with error code
 */

#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>

namespace utils {
struct error : std::stringstream {
  ~error() {
    std::cerr << "ERROR: " << str() << std::endl;
    glfwTerminate();
    exit(1);
  }
};
} // namespace utils
#endif // !UTILS_ERROR_HPP_
