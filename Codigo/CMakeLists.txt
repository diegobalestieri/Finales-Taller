cmake_minimum_required(VERSION 3.9)
project(Codigo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
add_executable(Codigo main.cpp SumadorProtegido.cpp SumadorProtegido.h ContadorDeInstancias.cpp ContadorDeInstancias.h Interseccion.cpp)