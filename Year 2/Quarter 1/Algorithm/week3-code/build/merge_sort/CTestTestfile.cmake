# CMake generated Testfile for 
# Source directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/merge_sort
# Build directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/build/merge_sort
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(merge_sort_test "python3" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/scripts/test_sorting.py" "merge_sort" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/merge_sort/tests/merge_sort_test_cases")
set_tests_properties(merge_sort_test PROPERTIES  WORKING_DIRECTORY "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/build/merge_sort" _BACKTRACE_TRIPLES "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/merge_sort/CMakeLists.txt;11;add_test;/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/merge_sort/CMakeLists.txt;0;")
