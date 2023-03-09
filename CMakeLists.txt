cmake_minimum_required(VERSION 3.24)
project(lab1 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab1 c_codes/lab1.c c_codes/utilities.c h_files/utilities.h h_files/commands.h)
