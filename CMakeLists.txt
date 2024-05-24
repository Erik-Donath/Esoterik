cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("./Brainfuck/")

project(brainfuck-executable)
add_executable(brainfuck-executable src/BrainfuckExe.cpp)
target_link_libraries(brainfuck-executable brainfuck)
