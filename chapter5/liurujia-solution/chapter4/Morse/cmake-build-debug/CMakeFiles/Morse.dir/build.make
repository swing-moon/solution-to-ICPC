# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /opt/clion-2018.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fogsail/liurujia-solution/chapter4/Morse

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fogsail/liurujia-solution/chapter4/Morse/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Morse.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Morse.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Morse.dir/flags.make

CMakeFiles/Morse.dir/main.cpp.o: CMakeFiles/Morse.dir/flags.make
CMakeFiles/Morse.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fogsail/liurujia-solution/chapter4/Morse/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Morse.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Morse.dir/main.cpp.o -c /home/fogsail/liurujia-solution/chapter4/Morse/main.cpp

CMakeFiles/Morse.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Morse.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fogsail/liurujia-solution/chapter4/Morse/main.cpp > CMakeFiles/Morse.dir/main.cpp.i

CMakeFiles/Morse.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Morse.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fogsail/liurujia-solution/chapter4/Morse/main.cpp -o CMakeFiles/Morse.dir/main.cpp.s

CMakeFiles/Morse.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Morse.dir/main.cpp.o.requires

CMakeFiles/Morse.dir/main.cpp.o.provides: CMakeFiles/Morse.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Morse.dir/build.make CMakeFiles/Morse.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Morse.dir/main.cpp.o.provides

CMakeFiles/Morse.dir/main.cpp.o.provides.build: CMakeFiles/Morse.dir/main.cpp.o


# Object files for target Morse
Morse_OBJECTS = \
"CMakeFiles/Morse.dir/main.cpp.o"

# External object files for target Morse
Morse_EXTERNAL_OBJECTS =

Morse: CMakeFiles/Morse.dir/main.cpp.o
Morse: CMakeFiles/Morse.dir/build.make
Morse: CMakeFiles/Morse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fogsail/liurujia-solution/chapter4/Morse/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Morse"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Morse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Morse.dir/build: Morse

.PHONY : CMakeFiles/Morse.dir/build

CMakeFiles/Morse.dir/requires: CMakeFiles/Morse.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Morse.dir/requires

CMakeFiles/Morse.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Morse.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Morse.dir/clean

CMakeFiles/Morse.dir/depend:
	cd /home/fogsail/liurujia-solution/chapter4/Morse/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fogsail/liurujia-solution/chapter4/Morse /home/fogsail/liurujia-solution/chapter4/Morse /home/fogsail/liurujia-solution/chapter4/Morse/cmake-build-debug /home/fogsail/liurujia-solution/chapter4/Morse/cmake-build-debug /home/fogsail/liurujia-solution/chapter4/Morse/cmake-build-debug/CMakeFiles/Morse.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Morse.dir/depend
