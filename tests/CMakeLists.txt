add_executable(window window.cpp)
add_executable(renderBox renderBox.cpp)
add_executable(modelTest modelTest.cpp)
add_executable(modelAndProjection modelAndProjection.cpp)

target_link_libraries(window ${SRC_LIB})
target_link_libraries(renderBox ${SRC_LIB} ${OPENGL_LIBS})
target_link_libraries(modelTest ${SRC_LIB})
target_link_libraries(modelAndProjection  ${SRC_LIB} ${OPENGL_LIBS})

