cmake_minimum_required(VERSION 2.8)
project(nts)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

add_executable(main
  include/organism.hpp
  include/location.hpp
  include/state.hpp
  include/day.hpp
  src/random.hpp
  include/simulation.hpp
  src/organism.cpp
  src/location.cpp
  src/state.cpp
  src/day.cpp
  src/simulation.cpp
  src/main.cpp
                )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
target_include_directories(main PUBLIC include/)
target_include_directories(main PUBLIC ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )

target_link_libraries(main PUBLIC
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARIES}
  ${GLEW_LIBRARIES}
)


