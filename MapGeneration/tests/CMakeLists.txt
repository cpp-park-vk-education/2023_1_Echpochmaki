add_executable(generation_tests src/generation_test.cpp)
target_link_libraries(generation_tests ../inc GTest::gtest_main)

add_test(generation_tests generation_tests)