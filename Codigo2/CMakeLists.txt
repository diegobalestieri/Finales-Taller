cmake_minimum_required(VERSION 3.15)
project(Codigo2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
add_executable(Codigo2 main.cpp Contador.cpp Contador.h DuplicarSiPertenece.cpp)