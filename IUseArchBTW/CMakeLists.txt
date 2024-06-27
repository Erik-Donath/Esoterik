cmake_minimum_required(VERSION 3.9)

project(IUseArchBTW VERSION 1.0.0 DESCRIPTION "IUseArchBTW")
add_library(IUseArchBTW
        ./src/IUseArchBTW.cpp
        ./src/IUseArchBTW.h
)
target_link_libraries(IUseArchBTW brainfuck)
target_include_directories(IUseArchBTW PUBLIC ./src/)

set_target_properties(IUseArchBTW PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(IUseArchBTW PROPERTIES PUBLIC_HEADER ./src/IUseArchBTW.h)

project(IUseArchBTW_executable VERSION 1.0.0 DESCRIPTION "IUseArchBTW Executable")

add_executable(IUseArchBTW_executable ./src/Executable.cpp)
target_link_libraries(IUseArchBTW_executable IUseArchBTW)
set_target_properties(IUseArchBTW_executable PROPERTIES OUTPUT_NAME "IUseArchBTW")
