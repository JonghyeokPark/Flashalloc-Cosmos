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
include plugin/auth/CMakeFiles/auth.dir/depend.make

# Include the progress variables for this target.
include plugin/auth/CMakeFiles/auth.dir/progress.make

# Include the compile flags for this target's objects.
include plugin/auth/CMakeFiles/auth.dir/flags.make

plugin/auth/CMakeFiles/auth.dir/dialog.c.o: plugin/auth/CMakeFiles/auth.dir/flags.make
plugin/auth/CMakeFiles/auth.dir/dialog.c.o: plugin/auth/dialog.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object plugin/auth/CMakeFiles/auth.dir/dialog.c.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/plugin/auth && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/auth.dir/dialog.c.o   -c /home/csoyee/git/mysql-dwblr-salloc/plugin/auth/dialog.c

plugin/auth/CMakeFiles/auth.dir/dialog.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/auth.dir/dialog.c.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/plugin/auth && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/plugin/auth/dialog.c > CMakeFiles/auth.dir/dialog.c.i

plugin/auth/CMakeFiles/auth.dir/dialog.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/auth.dir/dialog.c.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/plugin/auth && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/plugin/auth/dialog.c -o CMakeFiles/auth.dir/dialog.c.s

# Object files for target auth
auth_OBJECTS = \
"CMakeFiles/auth.dir/dialog.c.o"

# External object files for target auth
auth_EXTERNAL_OBJECTS =

plugin/auth/auth.so: plugin/auth/CMakeFiles/auth.dir/dialog.c.o
plugin/auth/auth.so: plugin/auth/CMakeFiles/auth.dir/build.make
plugin/auth/auth.so: libservices/libmysqlservices.a
plugin/auth/auth.so: plugin/auth/CMakeFiles/auth.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared module auth.so"
	cd /home/csoyee/git/mysql-dwblr-salloc/plugin/auth && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/auth.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugin/auth/CMakeFiles/auth.dir/build: plugin/auth/auth.so

.PHONY : plugin/auth/CMakeFiles/auth.dir/build

plugin/auth/CMakeFiles/auth.dir/clean:
	cd /home/csoyee/git/mysql-dwblr-salloc/plugin/auth && $(CMAKE_COMMAND) -P CMakeFiles/auth.dir/cmake_clean.cmake
.PHONY : plugin/auth/CMakeFiles/auth.dir/clean

plugin/auth/CMakeFiles/auth.dir/depend:
	cd /home/csoyee/git/mysql-dwblr-salloc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/plugin/auth /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/plugin/auth /home/csoyee/git/mysql-dwblr-salloc/plugin/auth/CMakeFiles/auth.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugin/auth/CMakeFiles/auth.dir/depend

