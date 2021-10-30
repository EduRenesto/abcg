cmake_minimum_required(VERSION 3.11)

project(gl-ball)

add_executable(
	${PROJECT_NAME}
	gl_window.cpp
	block.cpp
	block_renderer.cpp
	ball.cpp
	ball_renderer.cpp
	paddle.cpp
	paddle_renderer.cpp
	ui_renderer.cpp
	world.cpp
	quad_tree.cpp
	main.cpp)

enable_abcg(${PROJECT_NAME})
