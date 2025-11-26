# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(RationalProject LANGUAGES CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable for the main program
add_executable(rational_calculator
    main.cpp          # Main program
    rational.cpp      # Rational class implementation
    rational_calc.cpp # Rational calculator implementation
)

# Include header files
target_include_directories(rational_calculator
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Enable warnings
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(rational_calculator PRIVATE -Wall -Wextra -pedantic)
endif()