cmake_minimum_required (VERSION 3.8)

file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(ZEENGINE-test ${TEST_SOURCES})

target_include_directories(ZEENGINE-test
    PRIVATE
        ${ZEENGINE_HOME}/include
        ${ZEENGINE_HOME}/src
        ${CPPUNITTEST_HOME}/include
)

target_link_libraries(ZEENGINE-test zeengine)
target_link_libraries(ZEENGINE-test CppUTest CppUTestExt)

#add_custom_command(TARGET ZEENGINE-test COMMAND ./ZEENGINE-test POST_BUILD)


