# CMake generated Testfile for 
# Source directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/expression_eval
# Build directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/build/expression_eval
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(expression_eval_test "python3" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/scripts/test_target.py" "expression_eval" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/expression_eval/tests/expression_eval_test_cases")
set_tests_properties(expression_eval_test PROPERTIES  WORKING_DIRECTORY "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/build/expression_eval" _BACKTRACE_TRIPLES "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/expression_eval/CMakeLists.txt;10;add_test;/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week3-code/expression_eval/CMakeLists.txt;0;")
