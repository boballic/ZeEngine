if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the SDL source code and call cmake from there")
endif()

cmake_minimum_required (VERSION 3.8)

project ("ZeEngine" VERSION 1.0.0 LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)" OFF)
set(ZEENGINE_HOME ${CMAKE_CURRENT_SOURCE_DIR})
set(CPPUNITTEST_HOME ${CMAKE_CURRENT_SOURCE_DIR}/libs/cpputest-3.8)


set(ZEENGINE_TEST ON)

file(GLOB SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ecs/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp)

add_library(zeengine ${SOURCE_FILES})

target_include_directories(zeengine
    PUBLIC
        $<INSTALL_INTERFACE:include> 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(zeengine PUBLIC cxx_std_17)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/zeengine)

install(TARGETS zeengine
    EXPORT zeengine-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name ZeEngine and not jsonutils
set_target_properties(zeengine PROPERTIES EXPORT_NAME ZeEngine)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT zeengine-targets
  FILE
    ZeEngineTargets.cmake
  NAMESPACE
    ZeEngine::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ZeEngineConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/ZeEngineConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ZeEngineConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ZeEngineConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ZeEngineConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
export(EXPORT zeengine-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/ZeEngineTargets.cmake NAMESPACE ZeEngine::)

#Register package in user's package registry
export(PACKAGE ZeEngine)

if(${ZEENGINE_TEST})
  add_subdirectory("libs/cpputest-3.8")
  add_subdirectory("tests")
endif()