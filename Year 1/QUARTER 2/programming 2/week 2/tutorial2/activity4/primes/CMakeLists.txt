add_executable(primes primes.c ../functions/functions.c)

target_include_directories(primes PRIVATE ../functions)