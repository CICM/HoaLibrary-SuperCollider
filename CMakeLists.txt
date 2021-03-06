project(HoaLibrary-SuperCollider)
cmake_minimum_required(VERSION 3.0)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

    set(SC_PLUGINS_PATH /usr/local/share/SuperCollider/Extensions
        CACHE PATH "SuperCollider plugins path"
        )

else(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

    set(SC_PLUGINS_PATH ~/Library/Application\ Support/SuperCollider/Extensions
        CACHE PATH "SuperCollider plugins path"
        )
endif()

set(SC_PATH ~/git/supercollider/
    CACHE PATH "SuperCollider sdk path"
    )

set(HOA_PATH ThirdParty/HoaLibrary-Light
    CACHE PATH "HoaLibrary path"
    )


FILE(GLOB SC_CLASS src/sc/Classes/*)

set(LIBRARY HoaLibrary)

include_directories(
    ${HOA_PATH}/Sources
    ${SC_PATH}/include/common
    ${SC_PATH}/include/plugin_interface
    ${SC_PATH}/external_libraries/libsndfile/
    )

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

set_property(TARGET Encoder Decoder Optim PROPERTY CXX_STANDARD 11)

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
