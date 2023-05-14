add_executable(system_tests src/SystemTests.cpp)
target_link_libraries(system_tests ../../Components GTest::gtest_main)

add_test(system_tests system_tests)