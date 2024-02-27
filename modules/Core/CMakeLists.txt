cmake_minimum_required(VERSION 3.27)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(CMakeDependentOption)

include_directories(external/glm)

option(ENGINE_CORE_SHARED "Build a shared version of the Core library" ON)

link_directories(../../external/SDL3/lib)
link_directories(../../external/SDL3_image/lib)
link_directories(../../external/SDL3_mixer/lib)
link_directories(../../external/SDL3_ttf/lib)
link_directories(../../external/SDL3_net/lib)

if(ENGINE_CORE_SHARED)
    message("Core Engine Using Shared Library ENGINE_CORE_SHARED = ${ENGINE_CORE_SHARED}")
    add_library(Core SHARED
            entities/src/GameEntity.cpp
            interfaces/src/RenderingSystemMock.cpp
            interfaces/src/InputSystemMock.cpp
            interfaces/src/PropertiesManager.cpp
            external/jsoncpp/src/lib_json/json_reader.cpp
            external/jsoncpp/src/lib_json/json_value.cpp
            external/jsoncpp/src/lib_json/json_writer.cpp
            src/ResourcesManager.cpp
            src/CoreSystem.cpp
    )
else(ENGINE_CORE_SHARED)
    message("Core Engine Using Static Library ENGINE_CORE_SHARED = ${ENGINE_CORE_SHARED}")
    add_library(Core STATIC
            entities/src/GameEntity.cpp
            interfaces/src/RenderingSystemMock.cpp
            interfaces/src/InputSystemMock.cpp
            interfaces/src/PropertiesManager.cpp
            external/jsoncpp/src/lib_json/json_reader.cpp
            external/jsoncpp/src/lib_json/json_value.cpp
            external/jsoncpp/src/lib_json/json_writer.cpp
            src/ResourcesManager.cpp
            src/CoreSystem.cpp
    )
endif(ENGINE_CORE_SHARED)