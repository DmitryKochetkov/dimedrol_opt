cmake_minimum_required(VERSION 3.15)
project(Optimization)

set(CMAKE_CXX_STANDARD 14)

add_executable(Optimization main.cpp MathFunction.cpp MathFunction.h Swarm.cpp Swarm.h PointFormat.h)