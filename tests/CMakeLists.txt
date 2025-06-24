add_executable(window window.cpp)
add_executable(renderBox renderBox.cpp)

target_link_libraries(window ${SRC_LIB})
target_link_libraries(renderBox ${SRC_LIB})
