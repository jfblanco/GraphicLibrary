cmake_minimum_required(VERSION 3.27)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(CMakeDependentOption)

include_directories(include)

link_directories(../../external/SDL3/lib)
link_directories(../../external/SDL3_image/lib)
link_directories(../../external/SDL3_mixer/lib)
link_directories(../../external/SDL3_ttf/lib)
link_directories(../../external/SDL3_net/lib)

option(ENGINE_INPUT_SHARED "Build a shared version of the Input Manager library" ON)

if(ENGINE_INPUT_SHARED)
    message("Input Manager Using Shared Library ENGINE_INPUT_SHARED = ${ENGINE_INPUT_SHARED}")
    add_library(EventLibrary SHARED
                src/EventManager.cpp
                include/EventListener.h
    )
else(ENGINE_INPUT_SHARED)
    message("Input Manager Using Static Library ENGINE_INPUT_SHARED = ${ENGINE_INPUT_SHARED}")
    add_library(EventLibrary STATIC
                src/EventManager.cpp
                include/EventListener.h
    )
endif(ENGINE_INPUT_SHARED)