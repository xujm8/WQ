# CMake generated Testfile for 
# Source directory: /home/xujiaman/Desktop/CMaketest
# Build directory: /home/xujiaman/Desktop/CMaketest
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_run "Demo" "5" "2")
add_test(test_usage "Demo")
add_test(test_10_5 "Demo" "10" "5")
add_test(test_2_10 "Demo" "2" "10")
set_tests_properties(test_2_10 PROPERTIES  PASS_REGULAR_EXPRESSION "is 1024")
subdirs(math)
