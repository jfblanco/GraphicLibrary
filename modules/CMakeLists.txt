cmake_minimum_required(VERSION 3.27)

add_subdirectory(Core)
add_subdirectory(Input)
add_subdirectory(Disk)

target_link_libraries(Core SDL3)
target_link_libraries(Core SDL3_image)
target_link_libraries(Core SDL3_mixer)
target_link_libraries(Core jsoncpp)

target_link_libraries(EventLibrary SDL3)
target_link_libraries(EventLibrary SDL3_image)
target_link_libraries(EventLibrary SDL3_mixer)
target_link_libraries(EventLibrary jsoncpp)

target_link_libraries(Disk SDL3)
target_link_libraries(Disk SDL3_image)
target_link_libraries(Disk SDL3_mixer)
target_link_libraries(Disk jsoncpp)