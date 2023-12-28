cmake_minimum_required(VERSION 3.27)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(CMakeDependentOption)

include_directories(include)

option(ENGINE_CORE_SHARED "Build a shared version of the Core library" ON)

if(ENGINE_CORE_SHARED)
    message("Core Engine Using Shared Library ENGINE_CORE_SHARED = ${ENGINE_CORE_SHARED}")
    add_library(Core SHARED
            src/GameBaseEntity.cpp)
else(ENGINE_CORE_SHARED)
    message("Core Engine Using Static Library ENGINE_CORE_SHARED = ${ENGINE_CORE_SHARED}")
    add_library(Core STATIC
            src/GameBaseEntity.cpp
    )
endif(ENGINE_CORE_SHARED)