SET(ACT activity3)

add_executable(${ACT} main.c split.c)
target_compile_options(${ACT} PRIVATE -Wall -Wextra -Werror)
target_link_libraries(${ACT} PRIVATE functions)
