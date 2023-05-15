cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Game VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules/)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)


add_subdirectory(MapGeneration)
add_subdirectory(Graphics)
add_subdirectory(events)
add_subdirectory(net)
add_subdirectory(ECS)

add_executable(app main.cpp Game.cpp MapGeneration/src/LevelManager.cpp Time/Timer.cpp ECS/src/EntityCreator.cpp) #pls fix this

target_include_directories(app PUBLIC ECS/Systems/inc/ ECS/Components/ MapGeneration/inc/ Time)
target_link_libraries(app sfml-graphics)
target_link_libraries(app sfml-system)
target_link_libraries(app sfml-window)
target_link_libraries(app sfml-network)

option(BUILD_TESTS "build tests" OFF)
if (BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
endif ()



