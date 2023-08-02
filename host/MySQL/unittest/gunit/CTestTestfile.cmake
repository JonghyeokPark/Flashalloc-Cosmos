# CMake generated Testfile for 
# Source directory: /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit
# Build directory: /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(merge_large_tests "merge_large_tests-t")
set_tests_properties(merge_large_tests PROPERTIES  _BACKTRACE_TRIPLES "/home/csoyee/git/mysql-dwblr-salloc/unittest/gunit/CMakeLists.txt;333;ADD_TEST;/home/csoyee/git/mysql-dwblr-salloc/unittest/gunit/CMakeLists.txt;0;")
add_test(merge_small_tests "merge_small_tests-t")
set_tests_properties(merge_small_tests PROPERTIES  _BACKTRACE_TRIPLES "/home/csoyee/git/mysql-dwblr-salloc/unittest/gunit/CMakeLists.txt;334;ADD_TEST;/home/csoyee/git/mysql-dwblr-salloc/unittest/gunit/CMakeLists.txt;0;")
subdirs("yassl")
subdirs("innodb")
