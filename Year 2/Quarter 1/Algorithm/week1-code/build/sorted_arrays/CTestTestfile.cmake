# CMake generated Testfile for 
# Source directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/sorted_arrays
# Build directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/build/sorted_arrays
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(sorted_array_test_insert "python3" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/scripts/test_target.py" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/build/sorted_arrays/sorted_arrays" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/sorted_arrays/tests/insert_cases")
set_tests_properties(sorted_array_test_insert PROPERTIES  WORKING_DIRECTORY "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/build/sorted_arrays" _BACKTRACE_TRIPLES "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/sorted_arrays/CMakeLists.txt;5;add_test;/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/sorted_arrays/CMakeLists.txt;0;")
add_test(sorted_array_test_contains "python3" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/scripts/test_target.py" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/build/sorted_arrays/sorted_arrays" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/sorted_arrays/tests/contains_cases")
set_tests_properties(sorted_array_test_contains PROPERTIES  WORKING_DIRECTORY "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/build/sorted_arrays" _BACKTRACE_TRIPLES "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/sorted_arrays/CMakeLists.txt;11;add_test;/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/sorted_arrays/CMakeLists.txt;0;")
add_test(sorted_array_test_remove "python3" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/scripts/test_target.py" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/build/sorted_arrays/sorted_arrays" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/sorted_arrays/tests/remove_cases")
set_tests_properties(sorted_array_test_remove PROPERTIES  WORKING_DIRECTORY "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/build/sorted_arrays" _BACKTRACE_TRIPLES "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/sorted_arrays/CMakeLists.txt;17;add_test;/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week1-code/sorted_arrays/CMakeLists.txt;0;")
