# CMake generated Testfile for 
# Source directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week5-code/median
# Build directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week5-code/build/median
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(median_test "python3" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week5-code/scripts/test.py" "median" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week5-code/median/tests/median_test_cases")
set_tests_properties(median_test PROPERTIES  WORKING_DIRECTORY "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week5-code/build/median" _BACKTRACE_TRIPLES "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week5-code/median/CMakeLists.txt;11;add_test;/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week5-code/median/CMakeLists.txt;0;")
