cmake_minimum_required(VERSION 3.20)
project(functions)

add_library(functions functions.c morefunctions.c)
target_compile_options(functions PRIVATE -Wall -Wextra -Werror)
target_include_directories(functions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
