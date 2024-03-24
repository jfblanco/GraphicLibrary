cmake_minimum_required(VERSION 3.27)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(CMakeDependentOption)

option(ENGINE_CORE_SHARED "Build a shared version of the Core library" ON)

link_directories(../../external/SDL2/lib)
link_directories(../../external/SDL2_image/lib)
link_directories(../../external/SDL2_mixer/lib)
link_directories(../../external/SDL2_ttf/lib)
link_directories(../../external/SDL2_net/lib)

if(ENGINE_CORE_SHARED)
    message("Core Engine Using Shared Library ENGINE_CORE_SHARED = ${ENGINE_CORE_SHARED}")
    add_library(Core SHARED
            entities/src/GameEntity.cpp
            entities/src/Renderable.cpp
            interfaces/src/RenderingSystemMock.cpp
            interfaces/src/InputSystemMock.cpp
            interfaces/src/PropertiesManager.cpp
            interfaces/src/ShaderManager.cpp
            interfaces/src/ShaderFactoryMock.cpp
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
            entities/src/Renderable.cpp
            interfaces/src/RenderingSystemMock.cpp
            interfaces/src/InputSystemMock.cpp
            interfaces/src/PropertiesManager.cpp
            interfaces/src/ShaderManager.cpp
            interfaces/src/ShaderFactoryMock.cpp
            external/jsoncpp/src/lib_json/json_reader.cpp
            external/jsoncpp/src/lib_json/json_value.cpp
            external/jsoncpp/src/lib_json/json_writer.cpp
            src/ResourcesManager.cpp
            src/CoreSystem.cpp
    )
endif(ENGINE_CORE_SHARED)

target_include_directories(Core PUBLIC external)
target_include_directories(Core PUBLIC external/SDL2/include)
target_include_directories(Core PUBLIC external/Glew/include)
target_include_directories(Core PUBLIC external/SDL2_image/include)
target_include_directories(Core PUBLIC external/SDL2_mixer/include)
target_include_directories(Core PUBLIC external/SDL2_ttf/include)
target_include_directories(Core PUBLIC external/SDL2_net/include)

target_link_directories(Core PUBLIC external/SDL2/lib)
target_link_directories(Core PUBLIC external/SDL2_image/lib)
target_link_directories(Core PUBLIC external/SDL2_mixer/lib)
target_link_directories(Core PUBLIC external/SDL2_ttf/lib)
target_link_directories(Core PUBLIC external/SDL2_net/lib)

target_link_libraries(Core SDL2)
target_link_libraries(Core SDL2main)
target_link_libraries(Core SDL2_image)
target_link_libraries(Core opengl32)
#target_link_libraries(Core SDL2_mixer)

message("[Core Module] Copying DLL dependencies into: ${CMAKE_CURRENT_BINARY_DIR}")
file(COPY external/SDL2/bin/SDL2.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY external/SDL2_mixer/bin/SDL3_mixer.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY external/SDL2_image/bin/SDL2_image.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY external/SDL2_ttf/bin/SDL3_ttf.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY external/SDL2_net/bin/SDL3_net.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY external/Glew/bin/glew32.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY external/jpeg/bin/libjpeg-9.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY external/libpng/bin/libpng16.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY external/zlib/bin/zlib.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

file(COPY res/assets/models DESTINATION "${CMAKE_BINARY_DIR}/src/res")
file(COPY res/assets/images DESTINATION "${CMAKE_BINARY_DIR}/src/res")
file(COPY res/properties.json DESTINATION "${CMAKE_BINARY_DIR}/src/res")
