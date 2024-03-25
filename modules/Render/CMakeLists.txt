cmake_minimum_required(VERSION 3.27)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(CMakeDependentOption)

link_directories(../../external/SDL2/lib)
link_directories(../../external/SDL2_image/lib)
link_directories(../../external/SDL3_mixer/lib)
link_directories(../../external/SDL3_ttf/lib)
link_directories(../../external/SDL3_net/lib)

option(ENGINE_RENDERER_SHARED "Build a shared version of the Input Manager library" ON)
SET(RENDER_ENGINE_CORE_FOLDER "" CACHE PATH "Full Path where Core code is located")

message("[Render Module] Core Folder: ${RENDER_ENGINE_CORE_FOLDER}")

include_directories(include)

if("" STREQUAL RENDER_ENGINE_CORE_FOLDER)
    message(FATAL_ERROR "RENDER_ENGINE_CORE_FOLDER is not set for Render Module")
endif("" STREQUAL RENDER_ENGINE_CORE_FOLDER)

if(ENGINE_RENDERER_SHARED)
    message("[Render Module] Using Shared Library ENGINE_RENDERER_SHARED = ${ENGINE_RENDERER_SHARED}")
    add_library(RenderLibrary SHARED
            src/ShaderFactoryOpenGL.cpp
            src/RenderableFactoryOpenGL.cpp
            src/MaterialOpenGL.cpp
            src/ShaderOpenGL.cpp
            src/RenderableOpenGL.cpp
            src/ShaderManagerOpenGL.cpp
            shaders/src/ColorShader.cpp
            shaders/src/NormalShader.cpp
            shaders/src/TextureShader.cpp
            shaders/src/LightningShader.cpp
            src/RendererOpenGL.cpp
    )
else(ENGINE_RENDERER_SHARED)
    message("[Render Module] Using Static Library ENGINE_RENDERER_SHARED = ${ENGINE_RENDERER_SHARED}")
    add_library(RenderLibrary STATIC
                src/ShaderFactoryOpenGL.cpp
                src/RenderableFactoryOpenGL.cpp
                src/ShaderManagerOpenGL.cpp
                src/MaterialOpenGL.cpp
                src/ShaderOpenGL.cpp
                src/RenderableOpenGL.cpp
                shaders/src/ColorShader.cpp
                shaders/src/NormalShader.cpp
                shaders/src/TextureShader.cpp
                shaders/src/LightningShader.cpp
            src/RendererOpenGL.cpp
    )
endif(ENGINE_RENDERER_SHARED)

target_include_directories(RenderLibrary PUBLIC include)
target_include_directories(RenderLibrary PUBLIC shaders/include)
target_include_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/interfaces)
target_include_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/interfaces/includes)
target_include_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/entities/include)
target_include_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external)
target_include_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/SDL2/include)
target_include_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/Glew/include)
target_include_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/SDL2_image/include)
target_include_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/SDL2_mixer/include)
target_include_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/SDL2_ttf/include)
target_include_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/SDL2_net/include)

target_link_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/SDL2/lib)
target_link_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/Glew/lib)
target_link_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/SDL2_image/lib)
target_link_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/SDL2_mixer/lib)
target_link_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/SDL2_ttf/lib)
target_link_directories(RenderLibrary PUBLIC ${RENDER_ENGINE_CORE_FOLDER}/external/SDL2_net/lib)

target_link_libraries(RenderLibrary SDL2)
target_link_libraries(RenderLibrary SDL2main)
target_link_libraries(RenderLibrary SDL2_image)
target_link_libraries(RenderLibrary SDL3_mixer)
target_link_libraries(RenderLibrary glew32)
target_link_libraries(RenderLibrary opengl32)

file(COPY res/shaders DESTINATION "${CMAKE_BINARY_DIR}/src/res")