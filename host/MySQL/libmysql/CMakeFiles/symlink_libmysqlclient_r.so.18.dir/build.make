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

# Utility rule file for symlink_libmysqlclient_r.so.18.

# Include the progress variables for this target.
include libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18.dir/progress.make

libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18: libmysql/libmysqlclient_r.so.18


libmysql/libmysqlclient_r.so.18: libmysql/libmysqlclient.so.18.1.0
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating libmysqlclient_r.so.18"
	cd /home/csoyee/git/mysql-dwblr-salloc/libmysql && /usr/local/bin/cmake -E remove -f /home/csoyee/git/mysql-dwblr-salloc/libmysql/libmysqlclient_r.so.18
	cd /home/csoyee/git/mysql-dwblr-salloc/libmysql && /usr/local/bin/cmake -E create_symlink libmysqlclient.so.18 libmysqlclient_r.so.18

symlink_libmysqlclient_r.so.18: libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18
symlink_libmysqlclient_r.so.18: libmysql/libmysqlclient_r.so.18
symlink_libmysqlclient_r.so.18: libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18.dir/build.make

.PHONY : symlink_libmysqlclient_r.so.18

# Rule to build all files generated by this target.
libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18.dir/build: symlink_libmysqlclient_r.so.18

.PHONY : libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18.dir/build

libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18.dir/clean:
	cd /home/csoyee/git/mysql-dwblr-salloc/libmysql && $(CMAKE_COMMAND) -P CMakeFiles/symlink_libmysqlclient_r.so.18.dir/cmake_clean.cmake
.PHONY : libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18.dir/clean

libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18.dir/depend:
	cd /home/csoyee/git/mysql-dwblr-salloc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/libmysql /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/libmysql /home/csoyee/git/mysql-dwblr-salloc/libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libmysql/CMakeFiles/symlink_libmysqlclient_r.so.18.dir/depend

