cmake_minimum_required(VERSION 3.25)
project(gameof9th)

set(CMAKE_CXX_STANDARD 23)

add_executable(gameof9th main.cpp gameState.cpp gameHistory.cpp solver.cpp)
