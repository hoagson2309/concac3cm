cmake_minimum_required(VERSION 3.22)
project(demo_week_03)

add_executable(bday_cal
        utils.h
        date.cpp
        date.h)

target_sources(bday_cal
        PRIVATE
        main.cpp)

target_compile_features(bday_cal PRIVATE cxx_std_20)
set_target_properties(bday_cal PROPERTIES CXX_EXTENSIONS OFF)

# Set options for gnu-like
target_compile_options(bday_cal PRIVATE
        # set warnings for all build types
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Wconversion -Wfloat-equal
        -Wlogical-not-parentheses -Wmissing-field-initializers -Wmissing-noreturn -Wundef
        -Wredundant-decls -Wshadow -Wswitch-enum>
        # optimisation in Release
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>

        # O3 optimisation Debug
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g -fno-omit-frame-pointer>
)

# Set options for MSVC
target_compile_options(bday_cal PRIVATE
        # set warnings for all build types
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>
        # debug optimisation in Debug
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
        # O3 optimisation in Release
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/RTC1 /Od /Zi>
)

# ASAN things
option(USE_ASAN "Use address sanitizer if available" OFF)

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
    endif ()

else ()
    message("Address Sanitizer disabled for MSVC builds")

endif (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

if (${USE_ASAN} AND ${HAS_ASAN})
    target_compile_options(bday_cal PRIVATE -fsanitize=address)
    target_link_options(bday_cal PRIVATE -fsanitize=address)
endif (${USE_ASAN} AND ${HAS_ASAN})

# automatic gitignore for build directories
if (NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
    file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif ()