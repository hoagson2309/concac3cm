cmake_minimum_required(VERSION 3.22)
project(demo_06)

add_executable(demo_06
        dictionary.cpp
        dictionary.h)

target_sources(demo_06
        PRIVATE
        main.cpp)

target_compile_features(demo_06 PRIVATE cxx_std_20)
set_target_properties(demo_06 PROPERTIES CXX_EXTENSIONS OFF)

# Set options for gnu-like
target_compile_options(demo_06 PRIVATE
        # set warnings for all build types
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Werror -Wconversion -Wfloat-equal
        -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wformat=2 -Wlogical-not-parentheses
        -Wmissing-field-initializers -Wmissing-format-attribute -Walloca -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wpointer-arith -Wundef
        -Wredundant-decls -Wshadow -Wstack-protector -Wswitch-enum -Wwrite-strings>

        $<$<CXX_COMPILER_ID:GNU>:-Wlogical-op -Walloc-zero>

        # optimisation in Release
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>

        # Og optimisation Debug
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g3 -fno-omit-frame-pointer>
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/words.txt ${PROJECT_BINARY_DIR}/words.txt COPYONLY)


# ASAN things
option(USE_ASAN "Use address sanitizer if available" ON)

set(HAS_ASAN FALSE)

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

    execute_process(COMMAND "${CMAKE_C_COMPILER}" -print-file-name=libasan.so
            OUTPUT_VARIABLE LIBASAN_PATH
            RESULT_VARIABLE ASAN_RESULT
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    if (USE_ASAN AND (${ASAN_RESULT} EQUAL 0) AND (NOT ${LIBASAN_PATH} STREQUAL ""))
        message("libasan found @${LIBASAN_PATH}")
        message("Address Sanitizer enabled. To disable it set USE_ASAN to OFF.\n")
        set(HAS_ASAN TRUE)
    elseif (USE_ASAN AND (${ASAN_RESULT} EQUAL 0) AND (${LIBASAN_PATH} STREQUAL ""))
        message("Address sanitizer NOT FOUND")
    endif ()

else ()
    message("Address Sanitizer disabled for MSVC builds")
endif (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

if (${USE_ASAN} AND ${HAS_ASAN})
    target_compile_options(demo_06 PRIVATE -fsanitize=address)
    target_link_options(demo_06 PRIVATE -fsanitize=address)
endif (${USE_ASAN} AND ${HAS_ASAN})

# automatic gitignore for build directories
if (NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
    file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif ()