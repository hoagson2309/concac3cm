cmake_minimum_required(VERSION 3.0)

add_executable(task_1_2 task_1_2.cpp Options.cpp NumberFinder.cpp)


target_compile_features(task_1_2 PRIVATE cxx_std_20)
set_target_properties(task_1_2 PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(task_1_2 PRIVATE -Wall -Wextra -Wpedantic)

configure_file(file.txt file.txt COPYONLY)