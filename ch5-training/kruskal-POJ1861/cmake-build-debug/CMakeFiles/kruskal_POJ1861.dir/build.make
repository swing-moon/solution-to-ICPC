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
CMAKE_SOURCE_DIR = /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/kruskal_POJ1861.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kruskal_POJ1861.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kruskal_POJ1861.dir/flags.make

CMakeFiles/kruskal_POJ1861.dir/main.cpp.o: CMakeFiles/kruskal_POJ1861.dir/flags.make
CMakeFiles/kruskal_POJ1861.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/kruskal_POJ1861.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kruskal_POJ1861.dir/main.cpp.o -c /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861/main.cpp

CMakeFiles/kruskal_POJ1861.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kruskal_POJ1861.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861/main.cpp > CMakeFiles/kruskal_POJ1861.dir/main.cpp.i

CMakeFiles/kruskal_POJ1861.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kruskal_POJ1861.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861/main.cpp -o CMakeFiles/kruskal_POJ1861.dir/main.cpp.s

# Object files for target kruskal_POJ1861
kruskal_POJ1861_OBJECTS = \
"CMakeFiles/kruskal_POJ1861.dir/main.cpp.o"

# External object files for target kruskal_POJ1861
kruskal_POJ1861_EXTERNAL_OBJECTS =

kruskal_POJ1861: CMakeFiles/kruskal_POJ1861.dir/main.cpp.o
kruskal_POJ1861: CMakeFiles/kruskal_POJ1861.dir/build.make
kruskal_POJ1861: CMakeFiles/kruskal_POJ1861.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable kruskal_POJ1861"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kruskal_POJ1861.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kruskal_POJ1861.dir/build: kruskal_POJ1861

.PHONY : CMakeFiles/kruskal_POJ1861.dir/build

CMakeFiles/kruskal_POJ1861.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kruskal_POJ1861.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kruskal_POJ1861.dir/clean

CMakeFiles/kruskal_POJ1861.dir/depend:
	cd /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861 /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861 /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861/cmake-build-debug /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861/cmake-build-debug /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch5-training/kruskal-POJ1861/cmake-build-debug/CMakeFiles/kruskal_POJ1861.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kruskal_POJ1861.dir/depend
