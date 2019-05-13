cmake_minimum_required (VERSION 3.8)

include_directories(${CPPUNITTEST_HOME}/include)

file(GLOB TEST_SOURCES ${ZEENGINE_SOURCE_DIR}/tests/*.cpp)
add_executable(ZEENGINE-test ${TEST_SOURCES})

target_link_libraries(ZEENGINE-test ZEENGINE-static)
target_link_libraries(ZEENGINE-test CppUTest CppUTestExt)

add_custom_command(TARGET ZEENGINE-test COMMAND ./ZEENGINE-test POST_BUILD)


