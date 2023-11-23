cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Tanks3D)

add_executable(Tanks3D src/main.cpp)

target_link_libraries(Tanks3D sfml-graphics)
target_link_libraries(Tanks3D sfml-window)
target_link_libraries(Tanks3D sfml-system)

add_library(window STATIC include/Window/window.hpp src/window.cpp)
target_include_directories(window PUBLIC include/Window/)
target_link_libraries(Tanks3D window)

add_library(player STATIC include/Player/player.hpp src/player.cpp)
target_include_directories(player PUBLIC include/Player/)
target_link_libraries(Tanks3D player)

add_library(object STATIC include/Object/object.hpp src/object.cpp)
target_include_directories(object PUBLIC include/Object/)
target_link_libraries(Tanks3D object)

add_library(map STATIC include/Map/map.hpp src/map.cpp)
target_include_directories(map PUBLIC include/Map/)
target_link_libraries(map object)
target_link_libraries(Tanks3D map)

add_library(camera STATIC include/Camera/camera.hpp src/camera.cpp)
target_include_directories(camera PUBLIC include/Camera/)
target_link_libraries(camera map)
target_link_libraries(camera player)
target_link_libraries(Tanks3D camera)

add_library(common STATIC include/Common/common.hpp src/common.cpp)
target_include_directories(common PUBLIC include/Common/)
target_link_libraries(Tanks3D common)
target_link_libraries(window common)
target_link_libraries(player common)
target_link_libraries(object common)
target_link_libraries(map common)
target_link_libraries(camera common)
