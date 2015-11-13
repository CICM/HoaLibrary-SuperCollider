set(SC_PATH ~/GIT/supercollider/)
set(HOA_PATH ThirdParty/HoaLibrary-light/)
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

add_library(Encoder MODULE
  src/Encoder.cpp
  )

add_library(Decoder MODULE
  src/Decoder.cpp
  )

add_library(Optim MODULE
  src/Optim.cpp
  )

set_property(TARGET Encoder Decoder Optim PROPERTY CXX_STANDARD 14)

target_compile_options(Encoder PUBLIC -O3)
target_compile_options(Decoder PUBLIC -O3)
target_compile_options(Optim PUBLIC -O3)