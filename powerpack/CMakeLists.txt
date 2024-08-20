cmake_minimum_required(VERSION 3.28)

set(module powerpack)
project(${module} VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)

add_executable(${module} main.c
        ../lib1/udp_sock.h
        ../include/config.h
        ../lib1/strutil.c
        ../lib1/strutil.h)

target_link_libraries(${module} PUBLIC lib1)

install(TARGETS ${module} DESTINATION .)
