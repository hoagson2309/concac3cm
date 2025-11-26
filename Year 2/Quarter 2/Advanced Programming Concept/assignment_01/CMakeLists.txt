cmake_minimum_required(VERSION 3.30)
project(assignment_01)

# Add library and tests
add_subdirectory(libptr)
add_subdirectory(tests)

# Main executable
add_executable(assignment_01 main.cpp)
target_link_libraries(assignment_01 PRIVATE libptr)

# C++ standard and compiler options
target_compile_definitions(assignment_01 PRIVATE cxx_std_23)
target_compile_options(assignment_01 PRIVATE -Wall -Wextra -pedantic)

# Optionally enable sanitizers
option(ENABLE_SANITIZERS TRUE)
if(ENABLE_SANITIZERS)
    target_compile_options(assignment_01 PRIVATE -fsanitize=undefined,address -fno-omit-frame-pointer -O0)
    target_link_options(assignment_01 PRIVATE -fsanitize=undefined,address)
endif()
