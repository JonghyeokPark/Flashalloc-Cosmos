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
include unittest/gunit/CMakeFiles/gmock.dir/depend.make

# Include the progress variables for this target.
include unittest/gunit/CMakeFiles/gmock.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/gunit/CMakeFiles/gmock.dir/flags.make

unittest/gunit/CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.o: unittest/gunit/CMakeFiles/gmock.dir/flags.make
unittest/gunit/CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.o: source_downloads/gmock-1.6.0/src/gmock-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/gunit/CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.o -c /home/csoyee/git/mysql-dwblr-salloc/source_downloads/gmock-1.6.0/src/gmock-all.cc

unittest/gunit/CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/source_downloads/gmock-1.6.0/src/gmock-all.cc > CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.i

unittest/gunit/CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/source_downloads/gmock-1.6.0/src/gmock-all.cc -o CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.s

# Object files for target gmock
gmock_OBJECTS = \
"CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.o"

# External object files for target gmock
gmock_EXTERNAL_OBJECTS =

unittest/gunit/libgmock.a: unittest/gunit/CMakeFiles/gmock.dir/__/__/source_downloads/gmock-1.6.0/src/gmock-all.cc.o
unittest/gunit/libgmock.a: unittest/gunit/CMakeFiles/gmock.dir/build.make
unittest/gunit/libgmock.a: unittest/gunit/CMakeFiles/gmock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgmock.a"
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && $(CMAKE_COMMAND) -P CMakeFiles/gmock.dir/cmake_clean_target.cmake
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gmock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/gunit/CMakeFiles/gmock.dir/build: unittest/gunit/libgmock.a

.PHONY : unittest/gunit/CMakeFiles/gmock.dir/build

unittest/gunit/CMakeFiles/gmock.dir/clean:
	cd /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit && $(CMAKE_COMMAND) -P CMakeFiles/gmock.dir/cmake_clean.cmake
.PHONY : unittest/gunit/CMakeFiles/gmock.dir/clean

unittest/gunit/CMakeFiles/gmock.dir/depend:
	cd /home/csoyee/git/mysql-dwblr-salloc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit /home/csoyee/git/mysql-dwblr-salloc/unittest/gunit/CMakeFiles/gmock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/gunit/CMakeFiles/gmock.dir/depend

