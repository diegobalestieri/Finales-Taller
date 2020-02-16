cmake_minimum_required(VERSION 3.10)
project(SDLDibujar)

set(CMAKE_CXX_STANDARD 11)

add_executable(SDLDibujar main.cpp)

target_link_libraries(SDLDibujar SDL2main SDL2_image SDL2)
