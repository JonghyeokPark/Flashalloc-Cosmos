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
include storage/federated/CMakeFiles/federated_embedded.dir/depend.make

# Include the progress variables for this target.
include storage/federated/CMakeFiles/federated_embedded.dir/progress.make

# Include the compile flags for this target's objects.
include storage/federated/CMakeFiles/federated_embedded.dir/flags.make

storage/federated/CMakeFiles/federated_embedded.dir/ha_federated.cc.o: storage/federated/CMakeFiles/federated_embedded.dir/flags.make
storage/federated/CMakeFiles/federated_embedded.dir/ha_federated.cc.o: storage/federated/ha_federated.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object storage/federated/CMakeFiles/federated_embedded.dir/ha_federated.cc.o"
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/federated && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/federated_embedded.dir/ha_federated.cc.o -c /home/csoyee/git/mysql-dwblr-salloc/storage/federated/ha_federated.cc

storage/federated/CMakeFiles/federated_embedded.dir/ha_federated.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/federated_embedded.dir/ha_federated.cc.i"
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/federated && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/csoyee/git/mysql-dwblr-salloc/storage/federated/ha_federated.cc > CMakeFiles/federated_embedded.dir/ha_federated.cc.i

storage/federated/CMakeFiles/federated_embedded.dir/ha_federated.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/federated_embedded.dir/ha_federated.cc.s"
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/federated && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/csoyee/git/mysql-dwblr-salloc/storage/federated/ha_federated.cc -o CMakeFiles/federated_embedded.dir/ha_federated.cc.s

# Object files for target federated_embedded
federated_embedded_OBJECTS = \
"CMakeFiles/federated_embedded.dir/ha_federated.cc.o"

# External object files for target federated_embedded
federated_embedded_EXTERNAL_OBJECTS =

storage/federated/libfederated_embedded.a: storage/federated/CMakeFiles/federated_embedded.dir/ha_federated.cc.o
storage/federated/libfederated_embedded.a: storage/federated/CMakeFiles/federated_embedded.dir/build.make
storage/federated/libfederated_embedded.a: storage/federated/CMakeFiles/federated_embedded.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/csoyee/git/mysql-dwblr-salloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libfederated_embedded.a"
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/federated && $(CMAKE_COMMAND) -P CMakeFiles/federated_embedded.dir/cmake_clean_target.cmake
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/federated && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/federated_embedded.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
storage/federated/CMakeFiles/federated_embedded.dir/build: storage/federated/libfederated_embedded.a

.PHONY : storage/federated/CMakeFiles/federated_embedded.dir/build

storage/federated/CMakeFiles/federated_embedded.dir/clean:
	cd /home/csoyee/git/mysql-dwblr-salloc/storage/federated && $(CMAKE_COMMAND) -P CMakeFiles/federated_embedded.dir/cmake_clean.cmake
.PHONY : storage/federated/CMakeFiles/federated_embedded.dir/clean

storage/federated/CMakeFiles/federated_embedded.dir/depend:
	cd /home/csoyee/git/mysql-dwblr-salloc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/storage/federated /home/csoyee/git/mysql-dwblr-salloc /home/csoyee/git/mysql-dwblr-salloc/storage/federated /home/csoyee/git/mysql-dwblr-salloc/storage/federated/CMakeFiles/federated_embedded.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : storage/federated/CMakeFiles/federated_embedded.dir/depend

