cmake_minimum_required(VERSION 3.17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)


set(VERSION_SHORT "2.1.1")
project(QtCustomPlot LANGUAGES CXX VERSION ${VERSION_SHORT})

option(BUILD_STATIC     "Build the static library"  ON)
option(BUILD_USE_OPENGL "Build with opengl"         OFF)

option(BUILD_EXAMPLES   "Build the examples"        OFF)

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

