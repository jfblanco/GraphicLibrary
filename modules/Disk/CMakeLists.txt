cmake_minimum_required(VERSION 3.27)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(CMakeDependentOption)

include_directories(include)

option(ENGINE_DISK_SHARED "Build a shared version of the Disk Manager library" ON)

if(ENGINE_DISK_SHARED)
    message("Disk Manager Using Shared Library ENGINE_DISK_SHARED = ${ENGINE_DISK_SHARED}")
    add_library(Disk SHARED
                src/ResourcesManager.cpp
    )
else(ENGINE_DISK_SHARED)
    message("Disk Manager Using Static Library ENGINE_DISK_SHARED = ${ENGINE_DISK_SHARED}")
    add_library(Disk STATIC
                src/ResourcesManager.cpp
    )
endif(ENGINE_DISK_SHARED)