SET(ACT activity1)

add_executable(${ACT} main.c utils.c)
target_compile_options(${ACT} PRIVATE -Wall -Wextra)
target_link_libraries(${ACT} PRIVATE functions)
