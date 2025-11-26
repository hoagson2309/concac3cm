cmake_minimum_required(VERSION 3.20)
project(rational_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rational_demo main.cpp rational.cpp)

target_compile_options(rational_demo PRIVATE 
    -Wall 
    -Wextra 
    -pedantic 
    -fsanitize=address 
    -fno-omit-frame-pointer
)

target_link_options(rational_demo PRIVATE 
    -fsanitize=address
)