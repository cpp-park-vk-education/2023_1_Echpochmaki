add_library(events src/events.cpp)
target_include_directories(events PUBLIC inc)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()