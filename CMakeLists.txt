cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ECS VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)



enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

include_directories(Graphics/include)
include_directories(ECS/Components)
include_directories(ECS)
set(Srcs "Graphics/src/main.cpp")
set(Hdrs  "Graphics/include/animatable.h"  "ECS/ECS.h" "ECS/Components/SpriteComponent.h" "ECS/Components/PositionComponent.h" "ECS/Components/AnimationComponent.h"
        "ECS/Components/VelocityComponent.h" "ECS/Components/AttackComponent.h" "ECS/Components/AttackComponent.h"
        "ECS/Components/HealthComponent.h" "ECS/Components/TargetComponent.h" "ECS/Components/CollisionComponent.h"
        "ECS/EntityManager.h"
        )

add_executable(ECS ${Srcs} ${Hdrs})
target_link_libraries(ECS sfml-graphics)
install(TARGETS ECS DESTINATION bin)



