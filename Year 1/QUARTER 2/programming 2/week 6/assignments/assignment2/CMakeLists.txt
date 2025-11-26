SET(ACT activity2)

add_executable(${ACT} main.c persons.c)
target_compile_options(${ACT} PRIVATE -Wall -Wextra -Werror)
target_link_libraries(${ACT} PRIVATE functions)

configure_file(calendar.txt calendar.txt COPYONLY)
