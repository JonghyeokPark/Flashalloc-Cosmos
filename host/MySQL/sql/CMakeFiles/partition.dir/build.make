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
include sql/CMakeFiles/partition.dir/depend.make

# Include the progress variables for this target.
include sql/CMakeFiles/partition.dir/progress.make

# Include the compile flags for this target's objects.
include sql/CMakeFiles/partition.dir/flags.make

sql/CMakeFiles/partition.dir/ha_partition.cc.o: sql/CMakeFiles/partition.dir/flags.make
sql/CMakeFiles/partition.dir/ha_partition.cc.o: sql/ha_partition.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sql/CMakeFiles/partition.dir/ha_partition.cc.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/sql && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/partition.dir/ha_partition.cc.o -c /home/csoyee/git/mysql-dwblr-salloc/sql/ha_partition.cc

sql/CMakeFiles/partition.dir/ha_partition.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/partition.dir/ha_partition.cc.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/sql && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/sql/ha_partition.cc > CMakeFiles/partition.dir/ha_partition.cc.i

sql/CMakeFiles/partition.dir/ha_partition.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/partition.dir/ha_partition.cc.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/sql && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/sql/ha_partition.cc -o CMakeFiles/partition.dir/ha_partition.cc.s

# Object files for target partition
partition_OBJECTS = \
"CMakeFiles/partition.dir/ha_partition.cc.o"

# External object files for target partition
partition_EXTERNAL_OBJECTS =

sql/libpartition.a: sql/CMakeFiles/partition.dir/ha_partition.cc.o
sql/libpartition.a: sql/CMakeFiles/partition.dir/build.make
sql/libpartition.a: sql/CMakeFiles/partition.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libpartition.a"
	cd /home/csoyee/git/mysql-dwblr-salloc/sql && $(CMAKE_COMMAND) -P CMakeFiles/partition.dir/cmake_clean_target.cmake
	cd /home/csoyee/git/mysql-dwblr-salloc/sql && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/partition.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sql/CMakeFiles/partition.dir/build: sql/libpartition.a

.PHONY : sql/CMakeFiles/partition.dir/build

sql/CMakeFiles/partition.dir/clean:
	cd /home/csoyee/git/mysql-dwblr-salloc/sql && $(CMAKE_COMMAND) -P CMakeFiles/partition.dir/cmake_clean.cmake
.PHONY : sql/CMakeFiles/partition.dir/clean

sql/CMakeFiles/partition.dir/depend:
	cd /home/csoyee/git/mysql-dwblr-salloc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/sql /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/sql /home/csoyee/git/mysql-dwblr-salloc/sql/CMakeFiles/partition.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sql/CMakeFiles/partition.dir/depend

