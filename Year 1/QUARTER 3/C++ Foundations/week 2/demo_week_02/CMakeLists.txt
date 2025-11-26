cmake_minimum_required(VERSION 3.22)
project(demo_week_02)

add_executable(grepper
        options.cpp
        options.h
        grepper.cpp
        grepper.h)

target_sources(grepper
        PRIVATE
        main.cpp)

target_compile_features(grepper PRIVATE cxx_std_20)
set_target_properties(grepper PROPERTIES CXX_EXTENSIONS OFF)

# Set options for gnu-like
target_compile_options(grepper PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wmissing-field-initializers -Wshadow
        -Og -g3 -fno-omit-frame-pointer)

target_compile_options(grepper PRIVATE -fsanitize=address,undefined)
target_link_options(grepper PRIVATE -fsanitize=address,undefined)


configure_file(main.cpp main.cpp COPYONLY)