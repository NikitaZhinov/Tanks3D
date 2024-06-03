cmake_minimum_required(VERSION 3.20)
project(Tanks3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRC src/*.cpp)
add_executable(Tanks3D ${SRC})
target_include_directories(Tanks3D PUBLIC include/)

target_link_libraries(Tanks3D sfml-graphics)
target_link_libraries(Tanks3D sfml-window)
target_link_libraries(Tanks3D sfml-system)
