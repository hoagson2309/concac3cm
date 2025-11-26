cmake_minimum_required(VERSION 3.20)
project(cppf)

add_executable(my_demo main.cpp cppf_string.cpp)

target_compile_options(my_demo PRIVATE -Wall -Wextra -pedantic -fsanitize=address -fno-omit-frame-pointer)
target_link_options(my_demo PRIVATE -fsanitize=address)