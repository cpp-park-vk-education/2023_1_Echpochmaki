cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ECS VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)



include_directories(Graphics/include)
include_directories(ECS/Components)
include_directories(ECS)
set(Srcs "Graphics/src/main.cpp")
set(Hdrs  "Graphics/include/animatable.h"  "ECS/ECS.h" "ECS/Components/SpriteComponent.h" "ECS/Components/PositionComponent.h" "ECS/Components/AnimationComponent.h"
        "Animation/Animation.h" "Animation/IAnimation.h" "ECS/Components/VelocityComponent.h")
add_executable(ECS ${Srcs} ${Hdrs})
target_link_libraries(ECS sfml-graphics)
install(TARGETS ECS DESTINATION bin)



