add_library(EntityManager src/EntityManager.cpp Components/AnimationMovingComponent.h)
target_include_directories(EntityManager PUBLIC inc)
include_directories(inc)

add_subdirectory(Systems)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()