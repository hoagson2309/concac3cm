cmake_minimum_required(VERSION 3.18)

project(find_the_bug)

add_executable(fdb main.cpp num_vector.cpp)

target_compile_features(fdb PRIVATE cxx_std_20)

set_target_properties(fdb PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(fdb PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_compile_options(fdb PRIVATE $<$<CONFIG:DEBUG>:-Og -g3 -fno-omit-frame-pointer>)
target_compile_options(fdb PRIVATE $<$<CONFIG:RELEASE>:-O2>)

option(ENABLE_SANITIZER "Enable sanitizers" OFF)

# check if sanitizers are available and enable them
include(CheckCXXCompilerFlag)

# need to set linker flags for the address sanitizer check, otherwise it fails
set(saved_crlo ${CMAKE_REQUIRED_LINK_OPTIONS})
set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
check_cxx_compiler_flag("-fsanitize=address" COMPILER_SUPPORTS_ASAN)
set (CMAKE_REQUIRED_LINK_OPTIONS ${saved_crlo})

CHECK_CXX_COMPILER_FLAG(-fsanitize=undefined COMPILER_SUPPORTS_USAN)

if(ENABLE_SANITIZER AND COMPILER_SUPPORTS_ASAN)
    message(STATUS "Compiler seems to support address sanitizer")
    target_compile_options(fdb PRIVATE $<$<AND:$<CONFIG:DEBUG>,$<CXX_COMPILER_ID:GNU,Clang,AppleClang>>:-fsanitize=address>)
    target_link_options(fdb PRIVATE $<$<AND:$<CONFIG:DEBUG>,$<CXX_COMPILER_ID:GNU,Clang,AppleClang>>:-fsanitize=address>)
else()
    message(STATUS "Address sanitizer disabled")
endif()

if(ENABLE_SANITIZER AND COMPILER_SUPPORTS_USAN)
    message(STATUS "Compiler seems to support undefined behavior sanitizer")
    target_compile_options(fdb PRIVATE $<$<AND:$<CONFIG:DEBUG>,$<CXX_COMPILER_ID:GNU,Clang,AppleClang>>:-fsanitize=undefined>)
    target_link_options(fdb PRIVATE $<$<AND:$<CONFIG:DEBUG>,$<CXX_COMPILER_ID:GNU,Clang,AppleClang>>:-fsanitize=undefined>)
else()
    message(STATUS "Undefined behavior sanitizer disabled")
endif()