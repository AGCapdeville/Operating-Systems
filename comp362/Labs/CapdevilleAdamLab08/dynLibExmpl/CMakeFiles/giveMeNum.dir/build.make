# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.13.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.13.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl

# Include any dependencies generated for this target.
include CMakeFiles/giveMeNum.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/giveMeNum.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/giveMeNum.dir/flags.make

CMakeFiles/giveMeNum.dir/giveMeNum.c.o: CMakeFiles/giveMeNum.dir/flags.make
CMakeFiles/giveMeNum.dir/giveMeNum.c.o: giveMeNum.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/giveMeNum.dir/giveMeNum.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/giveMeNum.dir/giveMeNum.c.o   -c /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl/giveMeNum.c

CMakeFiles/giveMeNum.dir/giveMeNum.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/giveMeNum.dir/giveMeNum.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl/giveMeNum.c > CMakeFiles/giveMeNum.dir/giveMeNum.c.i

CMakeFiles/giveMeNum.dir/giveMeNum.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/giveMeNum.dir/giveMeNum.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl/giveMeNum.c -o CMakeFiles/giveMeNum.dir/giveMeNum.c.s

# Object files for target giveMeNum
giveMeNum_OBJECTS = \
"CMakeFiles/giveMeNum.dir/giveMeNum.c.o"

# External object files for target giveMeNum
giveMeNum_EXTERNAL_OBJECTS =

lib/libgiveMeNum.dylib: CMakeFiles/giveMeNum.dir/giveMeNum.c.o
lib/libgiveMeNum.dylib: CMakeFiles/giveMeNum.dir/build.make
lib/libgiveMeNum.dylib: CMakeFiles/giveMeNum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library lib/libgiveMeNum.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/giveMeNum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/giveMeNum.dir/build: lib/libgiveMeNum.dylib

.PHONY : CMakeFiles/giveMeNum.dir/build

CMakeFiles/giveMeNum.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/giveMeNum.dir/cmake_clean.cmake
.PHONY : CMakeFiles/giveMeNum.dir/clean

CMakeFiles/giveMeNum.dir/depend:
	cd /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl /Users/adamcapdeville/Documents/CSUCI/comp362/Labs/CapdevilleAdamLab08/dynLibExmpl/CMakeFiles/giveMeNum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/giveMeNum.dir/depend

