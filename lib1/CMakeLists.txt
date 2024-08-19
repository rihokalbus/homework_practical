cmake_minimum_required(VERSION 3.28)
project(lib1 C)

set(CMAKE_C_STANDARD 17)

add_library(lib1 SHARED udp_sock.c
        strutil.c
        strutil.h
        pong.c
        pong.h
        ping_pong_size.h
        ping_pong_def.h
        ping_pong_util.c)
