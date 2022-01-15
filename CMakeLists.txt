cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -pedantic -pthread")
project(6lab)
add_executable(oop_exercise_06
Figure/Figure.cpp
Figure/Figure.hpp
Figure/Figure.tpp
Figure/Octahedron/Octahedron.cpp
Figure/Octahedron/Octahedron.h
Figure/Octahedron/Octahedron.tpp
Figure/Square/Square.cpp
Figure/Square/Square.h
Figure/Square/Square.tpp
Figure/Triangle/Triangle.cpp
Figure/Triangle/Triangle.h
Figure/Triangle/Triangle.tpp
Read_input/Read_input.cpp
Read_input/Read_input.hpp
Read_input/Read_input.tpp
main.cpp
)
