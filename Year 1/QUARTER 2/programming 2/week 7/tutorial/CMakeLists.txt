cmake_minimum_required(VERSION 3.20)

project(Week7Tutorial)

add_executable(activity1 activity1.c)
target_compile_options(activity1 PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(activity2 activity2.c)
target_compile_options(activity2 PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(activity3 activity3.c)
target_compile_options(activity3 PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(activity4 activity4.c)
target_compile_options(activity4 PRIVATE -Wall -Wextra -Wpedantic)

add_executable(activity5 activity5.c)
target_compile_options(activity5 PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(activity6 activity6.c)
target_compile_options(activity6 PRIVATE -Wall -Wextra -Wpedantic -Werror)

configure_file(numbers.txt numbers.txt COPYONLY)
configure_file(alice.txt alice.txt COPYONLY)
configure_file(--test.txt --test.txt COPYONLY)
