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
include regex/CMakeFiles/regex.dir/depend.make

# Include the progress variables for this target.
include regex/CMakeFiles/regex.dir/progress.make

# Include the compile flags for this target's objects.
include regex/CMakeFiles/regex.dir/flags.make

regex/CMakeFiles/regex.dir/regcomp.c.o: regex/CMakeFiles/regex.dir/flags.make
regex/CMakeFiles/regex.dir/regcomp.c.o: regex/regcomp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object regex/CMakeFiles/regex.dir/regcomp.c.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/regex.dir/regcomp.c.o   -c /home/csoyee/git/mysql-dwblr-salloc/regex/regcomp.c

regex/CMakeFiles/regex.dir/regcomp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/regex.dir/regcomp.c.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/regex/regcomp.c > CMakeFiles/regex.dir/regcomp.c.i

regex/CMakeFiles/regex.dir/regcomp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/regex.dir/regcomp.c.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/regex/regcomp.c -o CMakeFiles/regex.dir/regcomp.c.s

regex/CMakeFiles/regex.dir/regerror.c.o: regex/CMakeFiles/regex.dir/flags.make
regex/CMakeFiles/regex.dir/regerror.c.o: regex/regerror.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object regex/CMakeFiles/regex.dir/regerror.c.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/regex.dir/regerror.c.o   -c /home/csoyee/git/mysql-dwblr-salloc/regex/regerror.c

regex/CMakeFiles/regex.dir/regerror.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/regex.dir/regerror.c.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/regex/regerror.c > CMakeFiles/regex.dir/regerror.c.i

regex/CMakeFiles/regex.dir/regerror.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/regex.dir/regerror.c.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/regex/regerror.c -o CMakeFiles/regex.dir/regerror.c.s

regex/CMakeFiles/regex.dir/regexec.c.o: regex/CMakeFiles/regex.dir/flags.make
regex/CMakeFiles/regex.dir/regexec.c.o: regex/regexec.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object regex/CMakeFiles/regex.dir/regexec.c.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/regex.dir/regexec.c.o   -c /home/csoyee/git/mysql-dwblr-salloc/regex/regexec.c

regex/CMakeFiles/regex.dir/regexec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/regex.dir/regexec.c.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/regex/regexec.c > CMakeFiles/regex.dir/regexec.c.i

regex/CMakeFiles/regex.dir/regexec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/regex.dir/regexec.c.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/regex/regexec.c -o CMakeFiles/regex.dir/regexec.c.s

regex/CMakeFiles/regex.dir/regfree.c.o: regex/CMakeFiles/regex.dir/flags.make
regex/CMakeFiles/regex.dir/regfree.c.o: regex/regfree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object regex/CMakeFiles/regex.dir/regfree.c.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/regex.dir/regfree.c.o   -c /home/csoyee/git/mysql-dwblr-salloc/regex/regfree.c

regex/CMakeFiles/regex.dir/regfree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/regex.dir/regfree.c.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/regex/regfree.c > CMakeFiles/regex.dir/regfree.c.i

regex/CMakeFiles/regex.dir/regfree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/regex.dir/regfree.c.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/regex/regfree.c -o CMakeFiles/regex.dir/regfree.c.s

regex/CMakeFiles/regex.dir/reginit.c.o: regex/CMakeFiles/regex.dir/flags.make
regex/CMakeFiles/regex.dir/reginit.c.o: regex/reginit.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object regex/CMakeFiles/regex.dir/reginit.c.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/regex.dir/reginit.c.o   -c /home/csoyee/git/mysql-dwblr-salloc/regex/reginit.c

regex/CMakeFiles/regex.dir/reginit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/regex.dir/reginit.c.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/regex/reginit.c > CMakeFiles/regex.dir/reginit.c.i

regex/CMakeFiles/regex.dir/reginit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/regex.dir/reginit.c.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/regex/reginit.c -o CMakeFiles/regex.dir/reginit.c.s

# Object files for target regex
regex_OBJECTS = \
"CMakeFiles/regex.dir/regcomp.c.o" \
"CMakeFiles/regex.dir/regerror.c.o" \
"CMakeFiles/regex.dir/regexec.c.o" \
"CMakeFiles/regex.dir/regfree.c.o" \
"CMakeFiles/regex.dir/reginit.c.o"

# External object files for target regex
regex_EXTERNAL_OBJECTS =

regex/libregex.a: regex/CMakeFiles/regex.dir/regcomp.c.o
regex/libregex.a: regex/CMakeFiles/regex.dir/regerror.c.o
regex/libregex.a: regex/CMakeFiles/regex.dir/regexec.c.o
regex/libregex.a: regex/CMakeFiles/regex.dir/regfree.c.o
regex/libregex.a: regex/CMakeFiles/regex.dir/reginit.c.o
regex/libregex.a: regex/CMakeFiles/regex.dir/build.make
regex/libregex.a: regex/CMakeFiles/regex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C static library libregex.a"
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && $(CMAKE_COMMAND) -P CMakeFiles/regex.dir/cmake_clean_target.cmake
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/regex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
regex/CMakeFiles/regex.dir/build: regex/libregex.a

.PHONY : regex/CMakeFiles/regex.dir/build

regex/CMakeFiles/regex.dir/clean:
	cd /home/csoyee/git/mysql-dwblr-salloc/regex && $(CMAKE_COMMAND) -P CMakeFiles/regex.dir/cmake_clean.cmake
.PHONY : regex/CMakeFiles/regex.dir/clean

regex/CMakeFiles/regex.dir/depend:
	cd /home/csoyee/git/mysql-dwblr-salloc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/regex /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/regex /home/csoyee/git/mysql-dwblr-salloc/regex/CMakeFiles/regex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : regex/CMakeFiles/regex.dir/depend

