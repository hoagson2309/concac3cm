cmake_minimum_required(VERSION 3.20)

# Set the project name
project(Activity6)

# Find the ncurses library
find_package(Curses REQUIRED)

# Include the ncurses directories
target_include_directories(${CURSES_INCLUDE_DIR})

# Add the source file to the project
add_executable(activity6 main.c functions.c)

# options passed to compiler per target
target_compile_options(activity6 PRIVATE -Wall -Wextra -pedantic -Werror)

# Link the ncurses library to the executable
target_link_libraries(activity6 ${CURSES_LIBRARIES})