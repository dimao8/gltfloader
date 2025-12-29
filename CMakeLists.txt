cmake_minimum_required(VERSION 3.18)

# Project
project(gltfloader
  VERSION 0.1.0.25
  DESCRIPTION "glTF 2.0 loader"
  HOMEPAGE_URL ""
  LANGUAGES CXX
)
set(PACKAGE ${PROJECT_NAME})
set(VERSION ${PROJECT_VERSION})

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Compile options
set(CMAKE_CXX_STANDARD_REQUIRED 17)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-pedantic)
endif()

# Sources and headers
set(SOURCES
  src/accessor.cc
  src/accessorsparse.cc
  src/animation.cc
  src/animationchannel.cc
  src/animationsampler.cc
  src/animationtarget.cc
  src/asset.cc
  src/buffer.cc
  src/bufferview.cc
  src/camera.cc
  src/gltfloader.cc
  src/gltfnamedobject.cc
  src/gltfobject.cc
  src/image.cc
  src/material.cc
  src/mesh.cc
  src/normaltextureinfo.cc
  src/occlusiontextureinfo.cc
  src/orthographiccamera.cc
  src/sparseindices.cc
  src/sparsevalues.cc
  src/texture.cc
  src/textureinfo.cc
)

set(HEADERS
  src/accessor.h
  src/accessorsparse.h
  src/animation.h
  src/animationchannel.h
  src/animationsampler.h
  src/animationtarget.h
  src/asset.h
  src/buffer.h
  src/bufferview.h
  src/camera.h
  src/gltfnamedobject.h
  src/gltfobject.h
  src/gltftypes.h
  src/image.h
  src/material.h
  src/mesh.h
  src/normaltextureinfo.h
  src/occlusiontextureinfo.h
  src/orthographiccamera.h
  src/sparseindices.h
  src/sparsevalues.h
  src/texture.h
  src/textureinfo.h
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

# Check for pngloader
find_package(pngloader)

# Check for jpegloader
find_package(jpegloader)

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

# Docs
add_subdirectory(doc)

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
configure_file(
  ${CMAKE_SOURCE_DIR}/config.h.in
  ${CMAKE_BINARY_DIR}/config.h
  @ONLY
)
target_compile_definitions(
  gltfloader PRIVATE
  "-DHAVE_CONFIG_H"
)
