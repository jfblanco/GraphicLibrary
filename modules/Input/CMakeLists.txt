cmake_minimum_required(VERSION 3.27)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(CMakeDependentOption)

include_directories(include)

link_directories(../../external/SDL2/lib)
link_directories(../../external/SDL2_image/lib)
link_directories(../../external/SDL2_mixer/lib)
link_directories(../../external/SDL2_ttf/lib)
link_directories(../../external/SDL2_net/lib)

option(ENGINE_INPUT_SHARED "Build a shared version of the Input Manager library" ON)
SET(INPUT_ENGINE_CORE_FOLDER "" CACHE PATH "Full Path where Core code is located")

message("[Input Module] Core Folder: ${INPUT_ENGINE_CORE_FOLDER}")

if("" STREQUAL INPUT_ENGINE_CORE_FOLDER)
    message(FATAL_ERROR "INPUT_ENGINE_CORE_FOLDER is not set for Input Module")
endif("" STREQUAL INPUT_ENGINE_CORE_FOLDER)

if(ENGINE_INPUT_SHARED)
    message("[Input Module] Using Shared Library ENGINE_INPUT_SHARED = ${ENGINE_INPUT_SHARED}")
    add_library(EventLibrary SHARED
                src/EventManager.cpp
                include/EventListener.h
    )
else(ENGINE_INPUT_SHARED)
    message("[Input Module] Using Static Library ENGINE_INPUT_SHARED = ${ENGINE_INPUT_SHARED}")
    add_library(EventLibrary STATIC
                src/EventManager.cpp
                include/EventListener.h
    )
endif(ENGINE_INPUT_SHARED)

target_include_directories(EventLibrary PUBLIC include)
target_include_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/include)
target_include_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/interfaces)
target_include_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/external/SDL2/include)
target_include_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/external/SDL2_image/include)
target_include_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/external/SDL2_mixer/include)
target_include_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/external/SDL2_ttf/include)
target_include_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/external/SDL2_net/include)

target_link_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/external/SDL2/lib)
target_link_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/external/SDL2_image/lib)
target_link_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/external/SDL2_mixer/lib)
target_link_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/external/SDL2_ttf/lib)
target_link_directories(EventLibrary PUBLIC ${INPUT_ENGINE_CORE_FOLDER}/external/SDL2_net/lib)

target_link_libraries(EventLibrary SDL2)
target_link_libraries(EventLibrary SDL2main)
target_link_libraries(EventLibrary SDL2_image)
target_link_libraries(EventLibrary SDL3_mixer)
target_link_libraries(EventLibrary opengl32)