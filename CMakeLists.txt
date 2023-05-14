cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Game VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules/)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)





include_directories(Graphics/include)
include_directories(ECS/Components)
include_directories(ECS)
set(Srcs "main.cpp" MapGeneration/LevelManager.cpp)
set(Hdrs  "Graphics/include/animatable.h"  "ECS/ECS.h" "ECS/Components/SpriteComponent.h" "ECS/Components/PositionComponent.h" "ECS/Components/AnimationComponent.h"
        "ECS/Components/VelocityComponent.h" "ECS/Components/AttackComponent.h" "ECS/Components/AttackComponent.h"
        "ECS/Components/HealthComponent.h" "ECS/Components/TargetComponent.h" "ECS/Components/CollisionComponent.h"
        "ECS/Components/PlayerComponent.h" "ECS/Systems/inc/DrawSystem.h"
        "ECS/Systems/inc/BaseSystem.h" "ECS/Systems/inc/EnemySystem.h" "ECS/Systems/inc/HitBoxSystem.h"
        "ECS/Systems/inc/MoveSystem.h" "ECS/Systems/inc/PlayerSystem.h" "ECS/Systems/inc/SyncSystem.h"
        "ECS/EntityManager.h" "ECS/Tile.h" "ECS/Components/EnemyComponent.h"
        "net/Client.hpp" "net/IClient.hpp" "net/IHost.hpp" "net/Host.hpp" "net/Network.hpp"
        "map_generation/IMapGenerator.h" "map_generation/IRoomGenerator.h" "map_generation/LevelManager.h"
        "Animation/Animation.h" "Animation/IAnimation.h" "ECS/Systems/inc/EnemySystem.h" "ECS/Components/PlayerComponent.h" "ECS/Systems/inc/EnemySystem.h")


add_executable(Game ${Srcs} ${Hdrs})
target_link_libraries(Game sfml-graphics)
install(TARGETS Game DESTINATION bin)



