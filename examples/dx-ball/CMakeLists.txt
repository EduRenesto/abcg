cmake_minimum_required(VERSION 3.11)

project(dx-ball)

add_executable(${PROJECT_NAME} gl_window.cpp block_renderer.cpp ball_renderer.cpp world.cpp block.cpp quad_tree.cpp ball.cpp main.cpp)

enable_abcg(${PROJECT_NAME})
