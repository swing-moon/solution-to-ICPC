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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sculpture.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sculpture.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sculpture.dir/flags.make

CMakeFiles/sculpture.dir/main.cpp.o: CMakeFiles/sculpture.dir/flags.make
CMakeFiles/sculpture.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sculpture.dir/main.cpp.o"
	/usr/local/Cellar/gcc@6/6.4.0_2/bin/g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sculpture.dir/main.cpp.o -c /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture/main.cpp

CMakeFiles/sculpture.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sculpture.dir/main.cpp.i"
	/usr/local/Cellar/gcc@6/6.4.0_2/bin/g++-6 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture/main.cpp > CMakeFiles/sculpture.dir/main.cpp.i

CMakeFiles/sculpture.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sculpture.dir/main.cpp.s"
	/usr/local/Cellar/gcc@6/6.4.0_2/bin/g++-6 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture/main.cpp -o CMakeFiles/sculpture.dir/main.cpp.s

# Object files for target sculpture
sculpture_OBJECTS = \
"CMakeFiles/sculpture.dir/main.cpp.o"

# External object files for target sculpture
sculpture_EXTERNAL_OBJECTS =

sculpture: CMakeFiles/sculpture.dir/main.cpp.o
sculpture: CMakeFiles/sculpture.dir/build.make
sculpture: CMakeFiles/sculpture.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sculpture"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sculpture.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sculpture.dir/build: sculpture

.PHONY : CMakeFiles/sculpture.dir/build

CMakeFiles/sculpture.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sculpture.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sculpture.dir/clean

CMakeFiles/sculpture.dir/depend:
	cd /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture/cmake-build-debug /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture/cmake-build-debug /Users/zhangminchen/Downloads/research/solution-to-liurujia/chapter6/sculpture/cmake-build-debug/CMakeFiles/sculpture.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sculpture.dir/depend

