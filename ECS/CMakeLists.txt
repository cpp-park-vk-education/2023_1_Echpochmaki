cmake_minimum_required(VERSION 3.12)
project(Example)
set(This Example)

project(${This} C CXX)


set(CMAKE_CXX_STANDARD 20)

include_directories(ECS/Components)
include_directories(ECS)

enable_testing()
set(Headers ECS.h EntityManager.hpp)
set(Sources EntityManager.cpp)
add_library(Example STATIC ${Sources} ${Headers})

add_subdirectory(tests)