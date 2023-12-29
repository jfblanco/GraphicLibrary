cmake_minimum_required(VERSION 3.27)
project(EngineTest)

set(CMAKE_CXX_STANDARD 17)

include_directories(external/SDL3/include)
include_directories(external/SDL3_image/include)
include_directories(external/SDL3_mixer/include)
include_directories(external/SDL3_ttf/include)
include_directories(external/SDL3_net/include)
include_directories(external/jsoncpp/include)

link_directories(external/SDL3/lib)
link_directories(external/SDL3_image/lib)
link_directories(external/SDL3_mixer/lib)
link_directories(external/SDL3_ttf/lib)
link_directories(external/SDL3_net/lib)
link_directories(external/jsoncpp/lib)

include_directories(modules/Input/include)
include_directories(modules/Disk/include)
include_directories(modules/Render/include)

add_subdirectory(src)
add_subdirectory(modules)

file(COPY external/SDL3/bin/SDL3.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")
file(COPY external/SDL3_mixer/bin/SDL3_mixer.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")
file(COPY external/SDL3_image/bin/SDL3_image.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")
file(COPY external/SDL3_ttf/bin/SDL3_ttf.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")
file(COPY external/SDL3_net/bin/SDL3_net.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")
file(COPY external/jsoncpp/bin/jsoncpp.dll DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")