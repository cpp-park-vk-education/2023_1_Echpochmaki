cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ECS VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)



include_directories(Graphics/include)
set(Srcs "Graphics/src/main.cpp")
set(Hdrs  "Graphics/include/animatable.h"  "ECS/ECS.h" "ECS/SpriteComponent.h" "ECS/PositionComponent.h" "ECS/AnimationComponent.h"
        "Animation/Animation.h" "Animation/IAnimation.h" ECS/Systems/src/MoveSystem.cpp ECS/Systems/inc/MoveSystem.h ECS/Systems/src/BaseSystem.cpp ECS/Systems/inc/BaseSystem.h ECS/Systems/EntityManager.cpp ECS/EntityManager.h ECS/Systems/src/EnemySystem.cpp ECS/Systems/inc/EnemySystem.h ECS/Systems/src/PlayerSystem.cpp ECS/Systems/inc/PlayerSystem.h ECS/Systems/src/SyncSystem.cpp ECS/Systems/inc/SyncSystem.h ECS/Systems/src/HitBoxSystem.cpp ECS/Systems/inc/HitBoxSystem.h)
add_executable(ECS ${Srcs} ${Hdrs})
target_link_libraries(ECS sfml-graphics)
install(TARGETS ECS DESTINATION bin)



