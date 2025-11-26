cmake_minimum_required(VERSION 3.20)

project(Week4Tutorial)

add_executable(activity1 activity1.c functions.c)
target_compile_options(activity1 PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(activity2 activity2.c functions.c)
target_compile_options(activity2 PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(activity3 activity3.c functions.c)
target_compile_options(activity3 PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(activity4 activity4.c functions.c)
target_compile_options(activity4 PRIVATE -Wall -Wextra -Wpedantic -Werror -fsanitize=address)
target_link_options(activity4 PRIVATE -fsanitize=address)

add_executable(activity5 activity5.c functions.c)
target_compile_options(activity5 PRIVATE -Wall -Wextra -Wpedantic -Werror -fsanitize=address)
target_link_options(activity5 PRIVATE -fsanitize=address)

add_executable(activity6 activity6.c functions.c)
target_compile_options(activity6 PRIVATE -Wall -Wextra -Wpedantic -Werror -fsanitize=address)
target_link_options(activity6 PRIVATE -fsanitize=address)

add_executable(activity7 activity7.c functions.c)
target_compile_options(activity7 PRIVATE -Wall -Wextra -Wpedantic -Werror -fsanitize=address)
target_link_options(activity7 PRIVATE -fsanitize=address)

add_executable(activity8 activity8.c functions.c)
target_compile_options(activity8 PRIVATE -Wall -Wextra -Wpedantic -Werror -fsanitize=address)
target_link_options(activity8 PRIVATE -fsanitize=address)

