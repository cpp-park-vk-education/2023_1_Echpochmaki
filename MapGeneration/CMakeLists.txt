add_library(LevelManager src/LevelManager.cpp)
target_include_directories(LevelManager PUBLIC inc)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()