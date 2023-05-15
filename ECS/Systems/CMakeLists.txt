add_library(System src/BaseSystem.cpp src/EnemySystem.cpp
        src/HitBoxSystem.cpp src/MoveSystem.cpp
        src/PlayerSystem.cpp src/SyncSystem.cpp inc/AnimateMovingDirectionSystem.h inc/FramesSystem.h inc/CameraSystem.h inc/AttackSystem.h inc/RemoveEntitySystem.h)

include_directories(../inc/)
target_include_directories(System PUBLIC inc ../inc ../Components)


if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()