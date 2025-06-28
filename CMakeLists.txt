cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(
	UIToolkit
  LANGUAGES CXX  
)


add_compile_options(-g)
add_compile_definitions(DEBUG GLEW_NO_GLU GLFW_INCLUDE_NONE)

set(OPENGL_LIBS GLX glfw OpenGL GLEW)

find_package(glfw3 3.3.6 REQUIRED)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glm CONFIG REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)

file(GLOB_RECURSE SRC LIST_DIRECTORIES FALSE src/*.cpp)
set(SRC_LIB src_lib)

add_library(${SRC_LIB} STATIC ${SRC})

include_directories("include" ${VCPKG_INSTALLED_DIR}/opt/vcpkg/installed/x64-linux/include/)
target_link_libraries(${SRC_LIB} PRIVATE ${OPENGL_LIBS} OpenImageIO::OpenImageIO)

# for testing
add_executable(main main.cpp)
target_link_libraries(main ${SRC_LIB})

add_subdirectory("./tests/")
