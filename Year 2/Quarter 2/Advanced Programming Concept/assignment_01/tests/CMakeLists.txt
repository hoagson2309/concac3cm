cmake_minimum_required(VERSION 3.30)
project(tests)

set(target_up tests_unique)
add_executable(${target_up} test_unique.cpp)

# IMPORTANT: Include paths
target_include_directories(${target_up} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include              # doctest.h (tests/include)
    ${CMAKE_CURRENT_SOURCE_DIR}/../include           # your project includes
)

target_link_libraries(${target_up} PRIVATE libptr)

target_compile_features(${target_up} PRIVATE cxx_std_23)
target_compile_options(${target_up} PRIVATE -Wall -Wextra -pedantic -Wshadow -Wconversion)

# Sanitizers
target_compile_options(${target_up} PRIVATE -fsanitize=undefined,address -fno-omit-frame-pointer -O0)
target_link_options(${target_up} PRIVATE -fsanitize=undefined,address)

# Debug/Assertions/Grading flags
target_compile_definitions(${target_up} PRIVATE
    ENABLE_ASSERTIONS=1
    ENABLE_DEBUG=1
    ENABLE_GRADING=1
)
