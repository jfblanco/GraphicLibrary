add_executable(EngineTest
        events/CloseEvent.cpp)

target_sources(EngineTest PRIVATE main.cpp)

target_link_libraries(EngineTest
        PRIVATE SDL3
        PRIVATE SDL3_image
        PRIVATE SDL3_mixer
        PRIVATE Core
        PRIVATE EventLibrary
        PRIVATE Disk)

file(COPY assets DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

if(ENGINE_CORE_SHARED)
    add_custom_command(TARGET EngineTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/../modules/Core/Core.dll "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Created ${PROJECT_BINARY_DIR}/test_base.exe"
    )
endif(ENGINE_CORE_SHARED)

if(ENGINE_INPUT_SHARED)
    add_custom_command(TARGET EngineTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/../modules/Input/EventLibrary.dll "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Created ${PROJECT_BINARY_DIR}/test_base.exe"
    )
endif(ENGINE_INPUT_SHARED)

if(ENGINE_DISK_SHARED)
    add_custom_command(TARGET EngineTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/../modules/Disk/Disk.dll "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Created ${PROJECT_BINARY_DIR}/test_base.exe"
    )
endif(ENGINE_DISK_SHARED)
