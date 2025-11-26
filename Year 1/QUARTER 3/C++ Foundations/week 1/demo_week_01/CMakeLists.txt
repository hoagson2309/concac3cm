cmake_minimum_required(VERSION 3.22)
project(demo_week_01)

set(target demo_week_01)

add_executable(demo_week_01 main.cpp)


target_compile_features(demo_week_01 PRIVATE cxx_std_20)
set_target_properties(demo_week_01 PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(demo_week_01 PRIVATE -Wall -Wextra -pedantic -Wconversion)

configure_file(input.txt input.txt COPYONLY)  # copy input.txt to the binary output directory

if (NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
    file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif ()