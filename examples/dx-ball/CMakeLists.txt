cmake_minimum_required(VERSION 3.11)

project(dx-ball)

add_executable(${PROJECT_NAME} gl_window.cpp block_renderer.cpp main.cpp)

enable_abcg(${PROJECT_NAME})
