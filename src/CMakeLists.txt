add_executable(EngineTest)
target_sources(EngineTest PRIVATE main.cpp)
target_link_libraries(EngineTest external)

file(COPY assets DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
