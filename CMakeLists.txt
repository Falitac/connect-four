cmake_minimum_required(VERSION 3.10)

project(connect-four VERSION 0.1)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(connect-four ${SOURCES})

set_property(TARGET connect-four PROPERTY CXX_STANDARD 17)

target_link_libraries(connect-four sfml-graphics sfml-window sfml-system sfml-network tgui)
#target_link_libraries(connect-four glew32) 
#target_link_libraries(connect-four opengl32) 
