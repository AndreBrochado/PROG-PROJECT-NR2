cmake_minimum_required(VERSION 3.1)
project(Projecto_2_PROG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Board.cpp
    Board.h
    Bomb.cpp
    Bomb.h
    CMakeLists.txt
    Player.cpp
    Player.h
    projecto.cpp
    README.md
    ReadMe.txt
    Ship.cpp
    Ship.h
    Utilities.h)

add_executable(Projecto_2_PROG ${SOURCE_FILES} Utilities.cpp)