SET(ACT activity1)

add_executable(${ACT} main.c)
target_compile_options(${ACT} PRIVATE -Wall -Wextra -Werror)
target_link_libraries(${ACT} PRIVATE functions)

configure_file(input.txt input.txt COPYONLY)
