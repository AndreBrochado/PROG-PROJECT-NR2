cmake_minimum_required(VERSION 3.1)
project(ProgProjectnr2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Bomb.cpp
    Bomb.h
    projecto.cpp
    Utilities.h)

add_executable(ProgProjectnr2 ${SOURCE_FILES} Ship.cpp Ship.h Board.cpp Board.h Player.cpp Player.h)