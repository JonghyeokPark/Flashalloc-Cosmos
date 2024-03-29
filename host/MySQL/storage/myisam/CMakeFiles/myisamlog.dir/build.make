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
include storage/myisam/CMakeFiles/myisamlog.dir/depend.make

# Include the progress variables for this target.
include storage/myisam/CMakeFiles/myisamlog.dir/progress.make

# Include the compile flags for this target's objects.
include storage/myisam/CMakeFiles/myisamlog.dir/flags.make

storage/myisam/CMakeFiles/myisamlog.dir/myisamlog.c.o: storage/myisam/CMakeFiles/myisamlog.dir/flags.make
storage/myisam/CMakeFiles/myisamlog.dir/myisamlog.c.o: storage/myisam/myisamlog.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object storage/myisam/CMakeFiles/myisamlog.dir/myisamlog.c.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/myisam && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/myisamlog.dir/myisamlog.c.o   -c /home/csoyee/git/mysql-dwblr-salloc/storage/myisam/myisamlog.c

storage/myisam/CMakeFiles/myisamlog.dir/myisamlog.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/myisamlog.dir/myisamlog.c.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/myisam && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/storage/myisam/myisamlog.c > CMakeFiles/myisamlog.dir/myisamlog.c.i

storage/myisam/CMakeFiles/myisamlog.dir/myisamlog.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/myisamlog.dir/myisamlog.c.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/myisam && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/storage/myisam/myisamlog.c -o CMakeFiles/myisamlog.dir/myisamlog.c.s

# Object files for target myisamlog
myisamlog_OBJECTS = \
"CMakeFiles/myisamlog.dir/myisamlog.c.o"

# External object files for target myisamlog
myisamlog_EXTERNAL_OBJECTS =

storage/myisam/myisamlog: storage/myisam/CMakeFiles/myisamlog.dir/myisamlog.c.o
storage/myisam/myisamlog: storage/myisam/CMakeFiles/myisamlog.dir/build.make
storage/myisam/myisamlog: storage/myisam/libmyisam.a
storage/myisam/myisamlog: mysys/libmysys.a
storage/myisam/myisamlog: dbug/libdbug.a
storage/myisam/myisamlog: mysys/libmysys.a
storage/myisam/myisamlog: dbug/libdbug.a
storage/myisam/myisamlog: strings/libstrings.a
storage/myisam/myisamlog: zlib/libzlib.a
storage/myisam/myisamlog: storage/myisam/CMakeFiles/myisamlog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable myisamlog"
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/myisam && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myisamlog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
storage/myisam/CMakeFiles/myisamlog.dir/build: storage/myisam/myisamlog

.PHONY : storage/myisam/CMakeFiles/myisamlog.dir/build

storage/myisam/CMakeFiles/myisamlog.dir/clean:
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/myisam && $(CMAKE_COMMAND) -P CMakeFiles/myisamlog.dir/cmake_clean.cmake
.PHONY : storage/myisam/CMakeFiles/myisamlog.dir/clean

storage/myisam/CMakeFiles/myisamlog.dir/depend:
	cd /home/csoyee/git/mysql-dwblr-salloc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/storage/myisam /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/storage/myisam /home/csoyee/git/mysql-dwblr-salloc/storage/myisam/CMakeFiles/myisamlog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/myisam/CMakeFiles/myisamlog.dir/depend

