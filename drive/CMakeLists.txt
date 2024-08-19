cmake_minimum_required(VERSION 3.28)
project(drive C)

set(CMAKE_C_STANDARD 17)

add_executable(drive main.c
        ../lib1/ping.c
        ../include/config.h
        ../lib1/udp_sock.h
        ../lib1/strutil.c
        ../lib1/strutil.h)

target_link_libraries(drive PUBLIC lib1)