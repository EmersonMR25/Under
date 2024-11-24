# CMake generated Testfile for 
# Source directory: E:/PROJECTS/Under
# Build directory: E:/PROJECTS/Under/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[UnitTests]=] "E:/PROJECTS/Under/build/bin/UnitTests.exe")
set_tests_properties([=[UnitTests]=] PROPERTIES  _BACKTRACE_TRIPLES "E:/PROJECTS/Under/CMakeLists.txt;68;add_test;E:/PROJECTS/Under/CMakeLists.txt;0;")
subdirs("_deps/sfml-build")
