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

# installing
install(TARGETS ${module} DESTINATION .)

# testing
include(CTest)
set(test_dir tests)
enable_testing()

add_executable(test_strutil_log_format EXCLUDE_FROM_ALL ${test_dir}/test_strutil_log_format.c)
add_executable(test_strutil_loglevel EXCLUDE_FROM_ALL ${test_dir}/test_strutil_get_loglevel.c)

target_link_libraries(test_strutil_log_format ${module})

add_test(NAME strutil_log_format COMMAND test_strutil_log_format)
add_test(NAME strutil_loglevel_test COMMAND test_strutil_loglevel)
