# Packages : external libraries managed by
find_package(SFML COMPONENTS Graphics Window Audio System CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(api ${SRC_FILES} ${HEADER_FILES}
        include/ui/resource_ui.h
        include/gameplay/building.h
        include/gameplay/building_manager.h
        src/gameplay/building.cc
        src/gameplay/building_manger.cc
        src/ui/resource_ui.cc
        include/audio/audio_manager.h
        src/audio/audio_manager.cc)

target_include_directories(api PUBLIC include/)
target_link_libraries(api PUBLIC core SFML::System SFML::Graphics SFML::Audio SFML::Window)
