cmake_minimum_required(VERSION 3.10)
project(wc_clone)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wc_clone main.cpp options.cpp file_counts.cpp counter.cpp)

target_compile_options(wc_clone PRIVATE -Wall -Wextra -Wno-conversion -pedantic -std=c++20)

