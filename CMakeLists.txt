cmake_minimum_required(VERSION 2.8)
project(nts)

set(CMAKE_CXX_STANDARD 11)
add_executable(main
  include/organism.hpp
  include/location.hpp
  include/state.hpp
  include/day.hpp
  src/organism.cpp
  src/location.cpp
  src/state.cpp
  src/day.cpp
  src/main.cpp
                                )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
target_include_directories(main PUBLIC include/)


