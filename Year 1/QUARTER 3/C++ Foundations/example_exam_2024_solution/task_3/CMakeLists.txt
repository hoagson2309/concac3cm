cmake_minimum_required(VERSION 3.0)

add_executable(task_3 task_3.cpp IntVector.cpp)


target_compile_features(task_3 PRIVATE cxx_std_20)
set_target_properties(task_3 PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(task_3 PRIVATE -Wall -Wextra -Wpedantic)

target_compile_options(task_3 PRIVATE -fsanitize=address)
target_link_options(task_3 PRIVATE -fsanitize=address)

