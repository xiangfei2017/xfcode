# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /data/data/com.termux/files/usr/bin/sh

# The CMake executable.
CMAKE_COMMAND = /data/data/com.termux/files/usr/bin/cmake

# The command to remove a file.
RM = /data/data/com.termux/files/usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /data/data/com.termux/files/home/xfcode/ncurses_demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/data/com.termux/files/home/xfcode/ncurses_demo

# Include any dependencies generated for this target.
include CMakeFiles/cs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cs.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cs.dir/flags.make

CMakeFiles/cs.dir/cs.c.o: CMakeFiles/cs.dir/flags.make
CMakeFiles/cs.dir/cs.c.o: cs.c
CMakeFiles/cs.dir/cs.c.o: CMakeFiles/cs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/data/com.termux/files/home/xfcode/ncurses_demo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cs.dir/cs.c.o"
	/data/data/com.termux/files/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cs.dir/cs.c.o -MF CMakeFiles/cs.dir/cs.c.o.d -o CMakeFiles/cs.dir/cs.c.o -c /data/data/com.termux/files/home/xfcode/ncurses_demo/cs.c

CMakeFiles/cs.dir/cs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cs.dir/cs.c.i"
	/data/data/com.termux/files/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /data/data/com.termux/files/home/xfcode/ncurses_demo/cs.c > CMakeFiles/cs.dir/cs.c.i

CMakeFiles/cs.dir/cs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cs.dir/cs.c.s"
	/data/data/com.termux/files/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /data/data/com.termux/files/home/xfcode/ncurses_demo/cs.c -o CMakeFiles/cs.dir/cs.c.s

# Object files for target cs
cs_OBJECTS = \
"CMakeFiles/cs.dir/cs.c.o"

# External object files for target cs
cs_EXTERNAL_OBJECTS =

cs: CMakeFiles/cs.dir/cs.c.o
cs: CMakeFiles/cs.dir/build.make
cs: CMakeFiles/cs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/data/com.termux/files/home/xfcode/ncurses_demo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cs.dir/build: cs
.PHONY : CMakeFiles/cs.dir/build

CMakeFiles/cs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cs.dir/clean

CMakeFiles/cs.dir/depend:
	cd /data/data/com.termux/files/home/xfcode/ncurses_demo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/data/com.termux/files/home/xfcode/ncurses_demo /data/data/com.termux/files/home/xfcode/ncurses_demo /data/data/com.termux/files/home/xfcode/ncurses_demo /data/data/com.termux/files/home/xfcode/ncurses_demo /data/data/com.termux/files/home/xfcode/ncurses_demo/CMakeFiles/cs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cs.dir/depend

