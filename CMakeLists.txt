cmake_minimum_required(VERSION 3.1)
project(Projecto_2_PROG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Board.cpp
    Board.h
    Bomb.cpp
    Bomb.h
    cenas.txt
    Player.cpp
    Player.h
    projecto.cpp
    Ship.cpp
    Ship.h
    Utilities.cpp
    Utilities.h)

add_executable(Projecto_2_PROG ${SOURCE_FILES})