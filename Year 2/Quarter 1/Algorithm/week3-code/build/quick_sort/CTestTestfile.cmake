# CMake generated Testfile for 
# Source directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/quick_sort
# Build directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/build/quick_sort
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(quick_sort_test "python3" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/scripts/test_sorting.py" "quick_sort" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/quick_sort/tests/quick_sort_test_cases")
set_tests_properties(quick_sort_test PROPERTIES  WORKING_DIRECTORY "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/build/quick_sort" _BACKTRACE_TRIPLES "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/quick_sort/CMakeLists.txt;10;add_test;/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/quick_sort/CMakeLists.txt;0;")
