cmake_minimum_required(VERSION 3.27)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(CMakeDependentOption)

include_directories(include)

link_directories(../../external/SDL2/lib)
link_directories(../../external/SDL2_image/lib)
link_directories(../../external/SDL2_mixer/lib)
link_directories(../../external/SDL2_ttf/lib)
link_directories(../../external/SDL2_net/lib)

option(ENGINE_GUI_SHARED "Build a shared version of the Graphics User Interface library" ON)
SET(GUI_ENGINE_CORE_FOLDER "" CACHE PATH "Full Path where Core code is located")

message("[GUI Module] Core Folder: ${GUI_ENGINE_CORE_FOLDER}")

if("" STREQUAL GUI_ENGINE_CORE_FOLDER)
    message(FATAL_ERROR "GUI_ENGINE_CORE_FOLDER is not set for GUI Module")
endif("" STREQUAL GUI_ENGINE_CORE_FOLDER)

if(ENGINE_GUI_SHARED)
    message("[Input Module] Using Shared Library ENGINE_GUI_SHARED = ${ENGINE_GUI_SHARED}")
    add_library(GUILibrary SHARED
            src/GUIFactory.cpp
            src/GUIBase.cpp
            src/GUIWindow.cpp
            src/GUIManager.cpp
            src/GUIEditorWindows.cpp
    )
else(ENGINE_GUI_SHARED)
    message("[Input Module] Using Static Library ENGINE_GUI_SHARED = ${ENGINE_GUI_SHARED}")
    add_library(GUILibrary STATIC
            src/GUIFactory.cpp
            src/GUIBase.cpp
            src/GUIWindow.cpp
            src/GUIManager.cpp
            src/GUIEditorWindows.cpp
    )
endif(ENGINE_GUI_SHARED)

target_include_directories(GUILibrary PUBLIC include)
target_include_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/include)
target_include_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/interfaces)
target_include_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external)
target_include_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external/SDL2/include)
target_include_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external/SDL2_image/include)
target_include_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external/SDL2_mixer/include)
target_include_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external/SDL2_ttf/include)
target_include_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external/SDL2_net/include)

target_link_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external)
target_link_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external/SDL2/lib)
target_link_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external/SDL2_image/lib)
target_link_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external/SDL2_mixer/lib)
target_link_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external/SDL2_ttf/lib)
target_link_directories(GUILibrary PUBLIC ${GUI_ENGINE_CORE_FOLDER}/external/SDL2_net/lib)

target_link_libraries(GUILibrary SDL2)
target_link_libraries(GUILibrary SDL2main)
target_link_libraries(GUILibrary SDL2_image)
target_link_libraries(GUILibrary SDL3_mixer)
target_link_libraries(GUILibrary opengl32)