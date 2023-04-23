cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(SFMLBoilerplate VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)



include_directories(include)
set(Srcs "src/main.cpp")
set(Hdrs  "include/animatable.h")
add_executable(SFMLBoilerplate ${Srcs} ${Hdrs})

target_include_directories(SFMLBoilerplate PRIVATE "${PROJECT_BINARY_DIR}")
target_link_libraries(SFMLBoilerplate sfml-graphics)
install(TARGETS SFMLBoilerplate DESTINATION bin)



