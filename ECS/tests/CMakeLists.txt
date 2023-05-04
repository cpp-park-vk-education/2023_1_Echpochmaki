cmake_minimum_required(VERSION 3.8)
set(This ExampleTests)

set(Sources ecs_test.cpp)

include_directories(ECS/Components)
include_directories(ECS)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC gtest-main Example)

add_test(
        Name ${This}
        COMMAND ${This}
)