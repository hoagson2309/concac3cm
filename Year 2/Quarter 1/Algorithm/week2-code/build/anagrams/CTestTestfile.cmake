# CMake generated Testfile for 
# Source directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week2-code/anagrams
# Build directory: /mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week2-code/build/anagrams
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(anagrams_test "python3" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week2-code/scripts/test_target.py" "anagrams" "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week2-code/anagrams/tests/anagrams_cases")
set_tests_properties(anagrams_test PROPERTIES  WORKING_DIRECTORY "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week2-code/build/anagrams" _BACKTRACE_TRIPLES "/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week2-code/anagrams/CMakeLists.txt;8;add_test;/mnt/c/SAXION/Year 2/Quarter 1/Algorithm/week2-code/anagrams/CMakeLists.txt;0;")
