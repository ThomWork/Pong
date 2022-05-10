cmake_minimum_required(VERSION 3.0)
project( PongV4 CXX )

set( CMAKE_BULD_TYPE Debug )

include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/src
)

add_executable( testexec buildtest/PongV4.cpp )
target_link_libraries( testexec sfml-graphics sfml-system sfml-window )
