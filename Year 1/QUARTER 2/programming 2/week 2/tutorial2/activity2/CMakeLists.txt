cmake_minimum_required(VERSION 3.20)

project(numberfun)

add_executable(numberfun numberfun.c main.c functions.c)
target_compile_options(numberfun PRIVATE -Wall) 