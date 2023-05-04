add_executable(test_network src/test_network.cpp)
target_link_libraries(test_network Game
                                GTest::gtest_main
                                GTest::gmock)
                                            

add_test(test_network test_network)
