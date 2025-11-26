cmake_minimum_required(VERSION 3.10)

project(SampleExam)

add_executable(assignment1 assignment1.c students.c)
add_executable(assignment2 assignment2.c students.c)
add_executable(assignment3 assignment3.c students.c)
add_executable(assignment4 assignment4.c students.c)
add_executable(assignment5 assignment5.c students.c)
add_executable(assignment6 assignment6.c students.c)
add_executable(grades grades.c students.c)

target_compile_options(assignment1 PRIVATE -Wall -Wextra -pedantic)
target_compile_options(assignment2 PRIVATE -Wall -Wextra -pedantic)
target_compile_options(assignment3 PRIVATE -Wall -Wextra -pedantic)
target_compile_options(assignment4 PRIVATE -Wall -Wextra -pedantic)
target_compile_options(assignment5 PRIVATE -Wall -Wextra -pedantic)
target_compile_options(assignment6 PRIVATE -Wall -Wextra -pedantic)
target_compile_options(grades PRIVATE -Wall -Wextra -pedantic)

configure_file(students.txt students.txt COPYONLY)
