# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_SOURCE_DIR = /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/UVA11882.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/UVA11882.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/UVA11882.dir/flags.make

CMakeFiles/UVA11882.dir/main.cpp.o: CMakeFiles/UVA11882.dir/flags.make
CMakeFiles/UVA11882.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/UVA11882.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/UVA11882.dir/main.cpp.o -c /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882/main.cpp

CMakeFiles/UVA11882.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UVA11882.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882/main.cpp > CMakeFiles/UVA11882.dir/main.cpp.i

CMakeFiles/UVA11882.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UVA11882.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882/main.cpp -o CMakeFiles/UVA11882.dir/main.cpp.s

# Object files for target UVA11882
UVA11882_OBJECTS = \
"CMakeFiles/UVA11882.dir/main.cpp.o"

# External object files for target UVA11882
UVA11882_EXTERNAL_OBJECTS =

UVA11882: CMakeFiles/UVA11882.dir/main.cpp.o
UVA11882: CMakeFiles/UVA11882.dir/build.make
UVA11882: CMakeFiles/UVA11882.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable UVA11882"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/UVA11882.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/UVA11882.dir/build: UVA11882

.PHONY : CMakeFiles/UVA11882.dir/build

CMakeFiles/UVA11882.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/UVA11882.dir/cmake_clean.cmake
.PHONY : CMakeFiles/UVA11882.dir/clean

CMakeFiles/UVA11882.dir/depend:
	cd /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882 /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882 /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882/cmake-build-debug /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882/cmake-build-debug /Users/zhangminchen/Downloads/tools/solution-to-ICPC/chapter7/exercise/UVA11882/cmake-build-debug/CMakeFiles/UVA11882.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/UVA11882.dir/depend

