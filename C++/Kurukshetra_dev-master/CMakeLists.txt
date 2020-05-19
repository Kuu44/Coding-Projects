cmake_minimum_required(VERSION 3.13)
project(kurukshetra)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(kurukshetra main.cpp src/GameClient.cpp src/MainMenu.cpp src/Game.cpp src/Player.cpp src/ResourceHolder.cpp src/Platform.cpp src/Camera.cpp src/Animation.cpp src/Collider.cpp src/GameServer.cpp src/Enemy.cpp src/Bullet.cpp src/IpEnter.cpp)
include_directories(kurukshetra includes)
target_link_libraries(kurukshetra sfml-graphics sfml-window sfml-network sfml-audio sfml-system)
