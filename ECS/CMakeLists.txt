add_library(EntityManager src/EntityManager.cpp src/EntityCreator.cpp Components/AnimationMovingComponent.h Components/FramesComponent.h Components/SinkableComponent.h)
target_include_directories(EntityManager PUBLIC inc)
include_directories(inc)

add_subdirectory(Systems)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()