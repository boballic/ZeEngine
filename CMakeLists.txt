if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the SDL source code and call cmake from there")
endif()

# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("ZeEngine")

set(ZEENGINE_SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(ZEENGINE_BINARY_DIR ${CMAKE_BINARY_DIR})
set(CPPUNITTEST_HOME ${ZEENGINE_SOURCE_DIR}/libs/cpputest-3.8)
set(ZEENGINE_TEST ON)

# General source files
file(GLOB SOURCE_FILES
  ${ZEENGINE_SOURCE_DIR}/src/*.cpp
  ${ZEENGINE_SOURCE_DIR}/src/ecs/*.cpp
  ${ZEENGINE_SOURCE_DIR}/src/core/*.cpp)

include_directories(${ZEENGINE_SOURCE_DIR}/include)
include_directories(${ZEENGINE_SOURCE_DIR}/src)

add_library(ZEENGINE-static STATIC ${SOURCE_FILES})

if(${ZEENGINE_TEST})
  add_subdirectory("libs/cpputest-3.8")
  add_subdirectory("tests")
endif()