SET(ACT activity3)

add_executable(${ACT} main.c)
target_compile_options(${ACT} PRIVATE -Wall -Wextra -Werror -fsanitize=address)
target_link_libraries(${ACT} PRIVATE functions -fsanitize=address)

configure_file(users.txt users.txt COPYONLY)
