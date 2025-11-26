add_executable(main main.c)
target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Werror)
target_link_libraries(main PRIVATE mylib)
