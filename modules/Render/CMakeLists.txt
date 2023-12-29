cmake_minimum_required(VERSION 3.27)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(CMakeDependentOption)

include_directories(include)

option(ENGINE_RENDERER_SHARED "Build a shared version of the Input Manager library" ON)

if(ENGINE_RENDERER_SHARED)
    message("Render Manager Using Shared Library ENGINE_RENDERER_SHARED = ${ENGINE_RENDERER_SHARED}")
    add_library(RenderLibrary SHARED
            src/glad.c
            src/Renderer.cpp
    )
else(ENGINE_RENDERER_SHARED)
    message("Render Manager Using Static Library ENGINE_RENDERER_SHARED = ${ENGINE_RENDERER_SHARED}")
    add_library(RenderLibrary STATIC
                src/glad.c
                src/Renderer.cpp
    )
endif(ENGINE_RENDERER_SHARED)