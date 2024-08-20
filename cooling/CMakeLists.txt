cmake_minimum_required(VERSION 3.28)
set(module cooling)
project(${module} VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)

add_executable(${module} main.c
        ../include/config.h
        ../lib1/strutil.c
        ../lib1/strutil.h
        ../lib1/pong.h)

target_link_libraries(${module} PUBLIC lib1)

install(TARGETS ${module} DESTINATION .)
