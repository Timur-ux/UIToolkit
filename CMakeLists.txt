cmake_minimum_required(VERSION 3.10)

project(
	UIToolkit
  LANGUAGES CXX  
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g)
add_compile_definitions(DEBUG GLEW_NO_GLU)

set(OPENGL_LIBS GLX glfw OpenGL GLEW)

find_package(glfw3 3.3.6 REQUIRED)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glm CONFIG REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SRC LIST_DIRECTORIES FALSE src/*.cpp)
set(SRC_LIB src_lib)

add_library(${SRC_LIB} STATIC ${SRC})

target_include_directories(${SRC_LIB} PUBLIC "include")
target_link_libraries(${SRC_LIB} ${OPENGL_LIBS})

# for testing
add_executable(main main.cpp)
target_link_libraries(main ${SRC_LIB} GLX glfw OpenGL GLEW)
