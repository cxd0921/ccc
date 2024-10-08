cmake_minimum_required(VERSION 3.29)
project(TEST1 C)

set(CMAKE_C_STANDARD 11)

add_executable(main main.c)
add_executable(test1 test1.c)
add_executable(link BothWayLink.c)
