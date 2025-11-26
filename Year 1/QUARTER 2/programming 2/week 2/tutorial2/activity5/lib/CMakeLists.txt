add_library(mylib numberfun.c functions.c)
target_compile_options(mylib PRIVATE -Wall -Wextra -pedantic -Werror)
target_include_directories(mylib PUBLIC .)
