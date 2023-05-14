add_executable(ecs_tests src/componentTest.cpp src/ecsTest.cpp src/entityManagerTest.cpp)
target_link_libraries(ecs_tests ../inc ../Components GTest::gtest_main)

add_test(ecs_tests ecs_tests)