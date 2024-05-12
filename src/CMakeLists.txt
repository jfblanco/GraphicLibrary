add_executable(EngineTest
        events/CloseEvent.cpp)

target_sources(EngineTest PRIVATE main.cpp)

target_link_libraries(EngineTest
        PRIVATE SDL2
        PRIVATE SDL2_image
        PRIVATE SDL3_mixer
        PRIVATE Core
        PRIVATE EventLibrary
        PRIVATE GUILibrary
        PRIVATE RenderLibrary)

file(COPY assets DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

if(ENGINE_CORE_SHARED)
    message("[Program] ENGINE_CORE_SHARED enabled, copying ${CMAKE_BINARY_DIR}/modules/Core/Core.dll into ${CMAKE_CURRENT_BINARY_DIR}")
    add_custom_command(TARGET EngineTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Core/Core.dll ${CMAKE_CURRENT_BINARY_DIR})
endif(ENGINE_CORE_SHARED)

if(ENGINE_INPUT_SHARED)
    message("[Program] ENGINE_INPUT_SHARED enabled, copying ${CMAKE_BINARY_DIR}/modules/Input/EventLibrary.dll into ${CMAKE_CURRENT_BINARY_DIR}")
    add_custom_command(TARGET EngineTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Input/EventLibrary.dll ${CMAKE_CURRENT_BINARY_DIR})
endif(ENGINE_INPUT_SHARED)

if(ENGINE_RENDERER_SHARED)
    message("[Program] ENGINE_RENDERER_SHARED enabled, copying ${CMAKE_BINARY_DIR}/modules/Render/RenderLibrary.dll into ${CMAKE_CURRENT_BINARY_DIR}")
    add_custom_command(TARGET EngineTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Render/RenderLibrary.dll ${CMAKE_CURRENT_BINARY_DIR})
endif(ENGINE_RENDERER_SHARED)

if(GUI_RENDERER_SHARED)
    message("[Program] GUI_RENDERER_SHARED enabled, copying ${CMAKE_BINARY_DIR}/modules/GUI/GUILibrary.dll into ${CMAKE_CURRENT_BINARY_DIR}")
    add_custom_command(TARGET EngineTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/GUI/GUILibrary.dll ${CMAKE_CURRENT_BINARY_DIR})
endif(GUI_RENDERER_SHARED)

message("[Program] Copying DLL to executable folder: ${CMAKE_CURRENT_BINARY_DIR}")

add_custom_command(TARGET EngineTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Core/SDL2.dll ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET EngineTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Core/SDL2_image.dll ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET EngineTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Core/SDL3_mixer.dll ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET EngineTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Core/SDL3_net.dll ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET EngineTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Core/SDL3_ttf.dll ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET EngineTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Core/glew32.dll ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET EngineTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Core/libjpeg-9.dll ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET EngineTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Core/libpng16.dll ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET EngineTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/modules/Core/zlib.dll ${CMAKE_CURRENT_BINARY_DIR})
