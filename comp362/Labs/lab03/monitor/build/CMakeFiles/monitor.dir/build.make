# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lighthouse/Desktop/comp362/lab03/monitor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lighthouse/Desktop/comp362/lab03/monitor/build

# Include any dependencies generated for this target.
include CMakeFiles/monitor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/monitor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/monitor.dir/flags.make

CMakeFiles/monitor.dir/monitor.c.o: CMakeFiles/monitor.dir/flags.make
CMakeFiles/monitor.dir/monitor.c.o: ../monitor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lighthouse/Desktop/comp362/lab03/monitor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/monitor.dir/monitor.c.o"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/monitor.dir/monitor.c.o   -c /home/lighthouse/Desktop/comp362/lab03/monitor/monitor.c

CMakeFiles/monitor.dir/monitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monitor.dir/monitor.c.i"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lighthouse/Desktop/comp362/lab03/monitor/monitor.c > CMakeFiles/monitor.dir/monitor.c.i

CMakeFiles/monitor.dir/monitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monitor.dir/monitor.c.s"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lighthouse/Desktop/comp362/lab03/monitor/monitor.c -o CMakeFiles/monitor.dir/monitor.c.s

# Object files for target monitor
monitor_OBJECTS = \
"CMakeFiles/monitor.dir/monitor.c.o"

# External object files for target monitor
monitor_EXTERNAL_OBJECTS =

monitor: CMakeFiles/monitor.dir/monitor.c.o
monitor: CMakeFiles/monitor.dir/build.make
monitor: CMakeFiles/monitor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lighthouse/Desktop/comp362/lab03/monitor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable monitor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/monitor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/monitor.dir/build: monitor

.PHONY : CMakeFiles/monitor.dir/build

CMakeFiles/monitor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/monitor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/monitor.dir/clean

CMakeFiles/monitor.dir/depend:
	cd /home/lighthouse/Desktop/comp362/lab03/monitor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lighthouse/Desktop/comp362/lab03/monitor /home/lighthouse/Desktop/comp362/lab03/monitor /home/lighthouse/Desktop/comp362/lab03/monitor/build /home/lighthouse/Desktop/comp362/lab03/monitor/build /home/lighthouse/Desktop/comp362/lab03/monitor/build/CMakeFiles/monitor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/monitor.dir/depend

