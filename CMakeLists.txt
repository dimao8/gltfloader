cmake_minimum_required(VERSION 3.18)

# Project
project(gltfloader
  VERSION 0.1.0.1
  DESCRIPTION "glTF 2.0 loader"
  HOMEPAGE_URL ""
  LANGUAGES CXX
)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Compile options
set(CMAKE_CXX_STANDARD 17)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-pedantic)
endif()

# Sources and headers
set(SOURCES
  src/buffer.cc
  src/gltfloader.cc
  src/gltfnamedobject.cc
  src/gltfobject.cc
  src/image.cc
)

set(HEADERS
  src/buffer.h
  src/gltfnamedobject.h
  src/gltfobject.h
  src/image.h
)

set(INTERFACE_HEADERS
  include/gltfloader/gltfloader.h
)

# Library
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(
  gltfloader SHARED
  ${SOURCES}
)
target_include_directories(
  gltfloader PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
  $<INSTALL_INTERFACE:include/gltfloader>
)
set_target_properties(gltfloader PROPERTIES
  PUBLIC_HEADER "${INTERFACE_HEADERS}"
)

# Check for uuid
find_file(UUID_HEADER "uuid.h"
  PATHS "/usr/include/uuid/")
if(NOT UUID_HEADER)
  message(FATAL_ERROR "uuid.h not found")
else()
  get_filename_component(UUID_INCLUDE ${UUID_HEADER} PATH)
  target_include_directories(
    gltfloader PUBLIC
    ${UUID_INCLUDE}
  )
endif()

# Check for jsonloader
find_package(litejson)

# Configuration
set(INCLUDE_INSTALL_DIR include/ CACHE PATH "Headers install directory")
set(LIB_INSTALL_DIR lib/ CACHE PATH "Libraries install directory")
set(SYSCONFIG_INSTALL_DIR etc/gltfloader/ CACHE PATH "System Configuration install directory")
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/gltfloaderConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/gltfloaderConfig.cmake
  INSTALL_DESTINATION ${LIB_INSTALL_DIR}/gltfloader/cmake
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/gltfloaderConfigVersion.cmake
  VERSION 0.2.0
  COMPATIBILITY SameMajorVersion
)

# Install
install(
  TARGETS gltfloader
  EXPORT gltfloader-targets
  PUBLIC_HEADER DESTINATION include/gltfloader
)

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/gltfloaderConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/gltfloaderConfigVersion.cmake
  DESTINATION ${LIB_INSTALL_DIR}/cmake/gltfloader
)

# Config file
set(PACKAGE ${PROJECT_NAME})
set(VERSION ${PROJECT_VERSION})
configure_file(
  ${CMAKE_SOURCE_DIR}/config.h.in
  ${CMAKE_BINARY_DIR}/config.h
  @ONLY
)
target_compile_definitions(
  gltfloader PRIVATE
  "-DHAVE_CONFIG_H"
)
