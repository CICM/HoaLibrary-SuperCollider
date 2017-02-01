set(SC_PATH ~/git/supercollider/
    CACHE PATH "SuperCollider sdk path"
    )
set(HOA_PATH ThirdParty/HoaLibrary-Light
    CACHE PATH "HoaLibrary path"
    )
set(SC_PLUGINS_PATH ~/Library/Application\ Support/SuperCollider/Extensions
    CACHE PATH "SuperCollider plugins path"
    )
FILE(GLOB SC_CLASS src/sc/Classes/*)
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
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
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

install(
    TARGETS Encoder Decoder Optim
    LIBRARY DESTINATION ${SC_PLUGINS_PATH}/${LIBRARY}
    )
install(
    FILES ${SC_CLASS}
    DESTINATION ${SC_PLUGINS_PATH}/${LIBRARY}/Classes 
    )
