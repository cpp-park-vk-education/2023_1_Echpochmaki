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
add_subdirectory(ECS)

add_executable(app main.cpp)

option(BUILD_TESTS "build tests")
if (BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
endif ()



