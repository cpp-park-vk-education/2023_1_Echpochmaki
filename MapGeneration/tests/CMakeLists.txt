# даже когда я прописал option(BUILD_TESTS "build tests" OFF) 
# в основном симейке, тесты пытались линковаться и у них ничего не получалось
# из за чего вся сборка падала, так что я закомментировал этот файл

# add_executable(generation_tests src/generation_test.cpp)
# target_link_libraries(generation_tests gtest_main)

# add_test(generation_tests generation_tests)