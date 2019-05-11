cmake_minimum_required (VERSION 3.8)

include_directories(${CPPUNITTEST_HOME}/include)
file(GLOB TEST_SOURCES ${ZEENGINE_SOURCE_DIR}/tests/*.cpp)
add_library(ZEENGINE-test STATIC ${TEST_SOURCES})

target_link_libraries(ZEENGINE-test ZEENGINE-static)
target_link_libraries(ZEENGINE-test CppUTest CppUTestExt)
