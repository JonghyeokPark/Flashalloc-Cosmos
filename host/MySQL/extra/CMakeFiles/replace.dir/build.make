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
include extra/CMakeFiles/replace.dir/depend.make

# Include the progress variables for this target.
include extra/CMakeFiles/replace.dir/progress.make

# Include the compile flags for this target's objects.
include extra/CMakeFiles/replace.dir/flags.make

extra/CMakeFiles/replace.dir/replace.c.o: extra/CMakeFiles/replace.dir/flags.make
extra/CMakeFiles/replace.dir/replace.c.o: extra/replace.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object extra/CMakeFiles/replace.dir/replace.c.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/extra && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/replace.dir/replace.c.o   -c /home/csoyee/git/mysql-dwblr-salloc/extra/replace.c

extra/CMakeFiles/replace.dir/replace.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/replace.dir/replace.c.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/extra && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/extra/replace.c > CMakeFiles/replace.dir/replace.c.i

extra/CMakeFiles/replace.dir/replace.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/replace.dir/replace.c.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/extra && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/extra/replace.c -o CMakeFiles/replace.dir/replace.c.s

# Object files for target replace
replace_OBJECTS = \
"CMakeFiles/replace.dir/replace.c.o"

# External object files for target replace
replace_EXTERNAL_OBJECTS =

extra/replace: extra/CMakeFiles/replace.dir/replace.c.o
extra/replace: extra/CMakeFiles/replace.dir/build.make
extra/replace: mysys/libmysys.a
extra/replace: dbug/libdbug.a
extra/replace: mysys/libmysys.a
extra/replace: dbug/libdbug.a
extra/replace: strings/libstrings.a
extra/replace: zlib/libzlib.a
extra/replace: extra/CMakeFiles/replace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable replace"
	cd /home/csoyee/git/mysql-dwblr-salloc/extra && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/replace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extra/CMakeFiles/replace.dir/build: extra/replace

.PHONY : extra/CMakeFiles/replace.dir/build

extra/CMakeFiles/replace.dir/clean:
	cd /home/csoyee/git/mysql-dwblr-salloc/extra && $(CMAKE_COMMAND) -P CMakeFiles/replace.dir/cmake_clean.cmake
.PHONY : extra/CMakeFiles/replace.dir/clean

extra/CMakeFiles/replace.dir/depend:
	cd /home/csoyee/git/mysql-dwblr-salloc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/extra /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/extra /home/csoyee/git/mysql-dwblr-salloc/extra/CMakeFiles/replace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extra/CMakeFiles/replace.dir/depend
