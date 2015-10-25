set(SC_PATH ~/GIT/supercollider/)
set(HOA_PATH ~/GIT/HoaLibrary-light)
set(LIBRARY HoaLibrary)

include_directories(${SC_PATH}/include/plugin_interface)
include_directories(${SC_PATH}/include/common)

project(HoaLibrary-SuperCollider)
cmake_minimum_required(VERSION 3.0)

include_directories(
  ${HOA_PATH}/Sources
  ${SC_PATH}/include/plugin_interface
  ${SC_PATH}/include/common
  ${SC_PATH}/external_libraries/libsndfile/)

set(CMAKE_SHARED_MODULE_PREFIX "")
if(APPLE OR WIN32)
set(CMAKE_SHARED_MODULE_SUFFIX ".scx")
endif()

add_library(${LIBRARY} MODULE
  src/Encoder.cpp
  )

set_property(TARGET ${LIBRARY} PROPERTY CXX_STANDARD 14)