SET(ACT activity2)

add_executable(${ACT} main.c)
target_compile_options(${ACT} PRIVATE -Wall -Wextra -Werror)
target_link_libraries(${ACT} PRIVATE functions)
