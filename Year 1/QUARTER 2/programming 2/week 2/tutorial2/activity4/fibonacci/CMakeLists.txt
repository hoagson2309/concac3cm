add_executable(fibonacci fibonacci.c ../functions/functions.c)

target_include_directories(fibonacci PRIVATE ../functions)