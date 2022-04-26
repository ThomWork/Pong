cmake_minimum_required(VERSION 3.0)

set(CMAKE_BULD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-L/../libs/SFML -lsfml-graphics -lsfml-window -lsfml-system")

project(PongV4)

add_executable(
	testexec
	PongV4.cpp
)
