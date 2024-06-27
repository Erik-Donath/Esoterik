cmake_minimum_required(VERSION 3.9)

project(brainfuck VERSION 1.0.0 DESCRIPTION "Brainfuck")
add_library(brainfuck
        ./src/Brainfuck.cpp
        ./src/Brainfuck.h
)
target_include_directories(brainfuck PUBLIC ./src/)

set_target_properties(brainfuck PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(brainfuck PROPERTIES PUBLIC_HEADER ./src/Brainfuck.h)

project(brainfuck_executable VERSION 1.0.0 DESCRIPTION "Brainfuck Executable")

add_executable(brainfuck_executable ./src/Executable.cpp)
target_link_libraries(brainfuck_executable brainfuck)
set_target_properties(brainfuck_executable PROPERTIES OUTPUT_NAME "Brainfuck")
