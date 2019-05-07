cmake_minimum_required(VERSION 3.9)
project(array_list)

set(SOURCE_FILES 
    array_list.h 
    array_list.c
    main.c
    array_list_tests.c
    array_list_tests.h)
add_executable(array_list ${SOURCE_FILES})
