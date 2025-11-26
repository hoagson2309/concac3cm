SET(ACT activity3)

add_executable(${ACT} main.c morefuns.c)
target_compile_options(${ACT} PRIVATE -Wall -Wextra)
target_link_libraries(${ACT} PRIVATE functions)

configure_file(text.txt text.txt COPYONLY)
configure_file(integers.txt integers.txt COPYONLY)
