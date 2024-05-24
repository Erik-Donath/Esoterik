cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

project(BrainfuckExe)
add_executable(BrainfuckExe src/BrainfuckExe.cpp)
add_subdirectory("./Brainfuck/")
target_link_libraries(BrainfuckExe brainfuck)