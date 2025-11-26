cmake_minimum_required(VERSION 3.20)
project(week7)

# Executables for all activities

# You can exclude an assignment by putting a # in front of the add_subdirectory for that assignment, like this:
#   add_subdirectory(assignment1)

add_subdirectory(assignment1)
add_subdirectory(assignment2)

configure_file(alice.txt alice.txt COPYONLY)
configure_file(pooh.txt pooh.txt COPYONLY)
configure_file(--test.txt --test.txt COPYONLY)

