cmake_minimum_required(VERSION 3.27)
project(EngineTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(external/SDL3/include)
include_directories(external/SDL3_image/include)
include_directories(external/SDL3_mixer/include)
include_directories(external/SDL3_ttf/include)
include_directories(external/SDL3_net/include)

link_directories(external/SDL3/lib)
link_directories(external/SDL3_image/lib)
link_directories(external/SDL3_mixer/lib)
link_directories(external/SDL3_ttf/lib)
link_directories(external/SDL3_net/lib)

include_directories(modules/Input/include)
include_directories(modules/Disk/include)
include_directories(modules/Render/include)
include_directories(modules/Core/interfaces)
include_directories(modules/Core/external)

add_subdirectory(src)
add_subdirectory(modules)

file(COPY external/SDL3/bin/SDL3.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")
file(COPY external/SDL3_mixer/bin/SDL3_mixer.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")
file(COPY external/SDL3_image/bin/SDL3_image.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")
file(COPY external/SDL3_ttf/bin/SDL3_ttf.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")
file(COPY external/SDL3_net/bin/SDL3_net.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")
file(COPY modules/Core/res/properties.json DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src/res")