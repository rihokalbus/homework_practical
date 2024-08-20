cmake_minimum_required(VERSION 3.28)

set(module lib1)

project(${module} VERSION 1.0 LANGUAGES C)


set(CMAKE_C_STANDARD 17)

add_library(${module} SHARED udp_sock.c
        strutil.c
        strutil.h
        pong.c
        pong.h
        ping_pong_size.h
        ping_pong_def.h
        ping_pong_util.c)

install(TARGETS ${module} DESTINATION .)
