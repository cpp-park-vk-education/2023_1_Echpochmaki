add_library(EntityManager src/EntityManager.cpp)
target_include_directories(EntityManager PUBLIC inc)

add_subdirectory(Systems)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()