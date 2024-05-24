cmake_minimum_required(VERSION 3.9)

project(brainfuck VERSION 1.0.0 DESCRIPTION "Brainfuck")
add_library(brainfuck src/Brainfuck.h src/Brainfuck.cpp)
target_include_directories(brainfuck PUBLIC src/)

set_target_properties(brainfuck PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(brainfuck PROPERTIES PUBLIC_HEADER src/Brainfuck.h)
