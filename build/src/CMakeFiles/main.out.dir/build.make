# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/takac8/semestralka

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/takac8/semestralka/build

# Include any dependencies generated for this target.
include src/CMakeFiles/main.out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/main.out.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/main.out.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/main.out.dir/flags.make

src/CMakeFiles/main.out.dir/main.c.o: src/CMakeFiles/main.out.dir/flags.make
src/CMakeFiles/main.out.dir/main.c.o: /home/takac8/semestralka/src/main.c
src/CMakeFiles/main.out.dir/main.c.o: src/CMakeFiles/main.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/takac8/semestralka/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/main.out.dir/main.c.o"
	cd /home/takac8/semestralka/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/main.out.dir/main.c.o -MF CMakeFiles/main.out.dir/main.c.o.d -o CMakeFiles/main.out.dir/main.c.o -c /home/takac8/semestralka/src/main.c

src/CMakeFiles/main.out.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.out.dir/main.c.i"
	cd /home/takac8/semestralka/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/takac8/semestralka/src/main.c > CMakeFiles/main.out.dir/main.c.i

src/CMakeFiles/main.out.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.out.dir/main.c.s"
	cd /home/takac8/semestralka/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/takac8/semestralka/src/main.c -o CMakeFiles/main.out.dir/main.c.s

src/CMakeFiles/main.out.dir/menu.c.o: src/CMakeFiles/main.out.dir/flags.make
src/CMakeFiles/main.out.dir/menu.c.o: /home/takac8/semestralka/src/menu.c
src/CMakeFiles/main.out.dir/menu.c.o: src/CMakeFiles/main.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/takac8/semestralka/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/main.out.dir/menu.c.o"
	cd /home/takac8/semestralka/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/main.out.dir/menu.c.o -MF CMakeFiles/main.out.dir/menu.c.o.d -o CMakeFiles/main.out.dir/menu.c.o -c /home/takac8/semestralka/src/menu.c

src/CMakeFiles/main.out.dir/menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.out.dir/menu.c.i"
	cd /home/takac8/semestralka/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/takac8/semestralka/src/menu.c > CMakeFiles/main.out.dir/menu.c.i

src/CMakeFiles/main.out.dir/menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.out.dir/menu.c.s"
	cd /home/takac8/semestralka/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/takac8/semestralka/src/menu.c -o CMakeFiles/main.out.dir/menu.c.s

# Object files for target main.out
main_out_OBJECTS = \
"CMakeFiles/main.out.dir/main.c.o" \
"CMakeFiles/main.out.dir/menu.c.o"

# External object files for target main.out
main_out_EXTERNAL_OBJECTS =

src/main.out: src/CMakeFiles/main.out.dir/main.c.o
src/main.out: src/CMakeFiles/main.out.dir/menu.c.o
src/main.out: src/CMakeFiles/main.out.dir/build.make
src/main.out: /usr/lib/x86_64-linux-gnu/libcurses.so
src/main.out: /usr/lib/x86_64-linux-gnu/libform.so
src/main.out: src/CMakeFiles/main.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/takac8/semestralka/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable main.out"
	cd /home/takac8/semestralka/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/main.out.dir/build: src/main.out
.PHONY : src/CMakeFiles/main.out.dir/build

src/CMakeFiles/main.out.dir/clean:
	cd /home/takac8/semestralka/build/src && $(CMAKE_COMMAND) -P CMakeFiles/main.out.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/main.out.dir/clean

src/CMakeFiles/main.out.dir/depend:
	cd /home/takac8/semestralka/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/takac8/semestralka /home/takac8/semestralka/src /home/takac8/semestralka/build /home/takac8/semestralka/build/src /home/takac8/semestralka/build/src/CMakeFiles/main.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/main.out.dir/depend
