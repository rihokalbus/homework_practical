cmake_minimum_required(VERSION 3.28)
project(cooling C)

set(CMAKE_C_STANDARD 17)

add_executable(cooling main.c
        ../include/config.h
        ../lib1/strutil.c
        ../lib1/strutil.h
        ../lib1/pong.h)

target_link_libraries(cooling PUBLIC lib1)