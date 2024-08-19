cmake_minimum_required(VERSION 3.28)
project(powerpack C)

set(CMAKE_C_STANDARD 17)

add_executable(powerpack main.c
        ../lib1/udp_sock.h
        ../include/config.h
        ../lib1/strutil.c
        ../lib1/strutil.h)

target_link_libraries(powerpack PUBLIC lib1)