cmake_minimum_required(VERSION 3.20)

project(labs_week_5)

add_executable(count main.cpp word_counter.cpp)

target_compile_features(count PRIVATE cxx_std_20)

target_compile_options(count PRIVATE -Wall -Wextra -Wpedantic)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(count PRIVATE -O0 -ggdb)
else()
    target_compile_options(count PRIVATE -O3)
endif()

#Enable sanitizers with recovery if compiler is clang or gnu or apple-clang
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND (NOT WIN32) AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
    message(STATUS "Enabling sanitizers")
    target_compile_options(count PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -fsanitize-recover=address,undefined)
    target_link_options(count PRIVATE -fsanitize=address,undefined)
endif() 

configure_file(alice_eng.txt alice_eng.txt COPYONLY)

# Create gitignore file if it does not exist
if (NOT EXISTS "${CMAKE_SOURCE_DIR}/.gitignore")
    file(WRITE "${CMAKE_SOURCE_DIR}/.gitignore" "")
    file(APPEND "${CMAKE_SOURCE_DIR}/.gitignore" "/build\n")
    file(APPEND "${CMAKE_SOURCE_DIR}/.gitignore" "/.vscode\n")
    file(APPEND "${CMAKE_SOURCE_DIR}/.gitignore" "/.idea\n")
    file(APPEND "${CMAKE_SOURCE_DIR}/.gitignore" "/cmake-build-*\n")
endif()

