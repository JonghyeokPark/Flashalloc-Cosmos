# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/csoyee/git/mysql-dwblr-salloc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/csoyee/git/mysql-dwblr-salloc

# Include any dependencies generated for this target.
include unittest/gunit/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include unittest/gunit/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/gunit/CMakeFiles/gtest.dir/flags.make

unittest/gunit/CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.o: unittest/gunit/CMakeFiles/gtest.dir/flags.make
unittest/gunit/CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.o: source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/gunit/CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.o -c /home/csoyee/git/mysql-dwblr-salloc/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc

unittest/gunit/CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc > CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.i

unittest/gunit/CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc -o CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

unittest/gunit/libgtest.a: unittest/gunit/CMakeFiles/gtest.dir/__/__/source_downloads/gmock-1.6.0/gtest/src/gtest-all.cc.o
unittest/gunit/libgtest.a: unittest/gunit/CMakeFiles/gtest.dir/build.make
unittest/gunit/libgtest.a: unittest/gunit/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest.a"
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/gunit/CMakeFiles/gtest.dir/build: unittest/gunit/libgtest.a

.PHONY : unittest/gunit/CMakeFiles/gtest.dir/build

unittest/gunit/CMakeFiles/gtest.dir/clean:
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : unittest/gunit/CMakeFiles/gtest.dir/clean

unittest/gunit/CMakeFiles/gtest.dir/depend:
	cd /home/csoyee/git/mysql-dwblr-salloc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/gunit/CMakeFiles/gtest.dir/depend
