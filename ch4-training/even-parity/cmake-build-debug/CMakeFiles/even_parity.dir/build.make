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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/even_parity.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/even_parity.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/even_parity.dir/flags.make

CMakeFiles/even_parity.dir/main.cpp.o: CMakeFiles/even_parity.dir/flags.make
CMakeFiles/even_parity.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/even_parity.dir/main.cpp.o"
	/usr/local/Cellar/gcc@6/6.4.0_2/bin/g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/even_parity.dir/main.cpp.o -c /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity/main.cpp

CMakeFiles/even_parity.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/even_parity.dir/main.cpp.i"
	/usr/local/Cellar/gcc@6/6.4.0_2/bin/g++-6 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity/main.cpp > CMakeFiles/even_parity.dir/main.cpp.i

CMakeFiles/even_parity.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/even_parity.dir/main.cpp.s"
	/usr/local/Cellar/gcc@6/6.4.0_2/bin/g++-6 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity/main.cpp -o CMakeFiles/even_parity.dir/main.cpp.s

CMakeFiles/even_parity.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/even_parity.dir/main.cpp.o.requires

CMakeFiles/even_parity.dir/main.cpp.o.provides: CMakeFiles/even_parity.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/even_parity.dir/build.make CMakeFiles/even_parity.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/even_parity.dir/main.cpp.o.provides

CMakeFiles/even_parity.dir/main.cpp.o.provides.build: CMakeFiles/even_parity.dir/main.cpp.o


# Object files for target even_parity
even_parity_OBJECTS = \
"CMakeFiles/even_parity.dir/main.cpp.o"

# External object files for target even_parity
even_parity_EXTERNAL_OBJECTS =

even_parity: CMakeFiles/even_parity.dir/main.cpp.o
even_parity: CMakeFiles/even_parity.dir/build.make
even_parity: CMakeFiles/even_parity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable even_parity"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/even_parity.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/even_parity.dir/build: even_parity

.PHONY : CMakeFiles/even_parity.dir/build

CMakeFiles/even_parity.dir/requires: CMakeFiles/even_parity.dir/main.cpp.o.requires

.PHONY : CMakeFiles/even_parity.dir/requires

CMakeFiles/even_parity.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/even_parity.dir/cmake_clean.cmake
.PHONY : CMakeFiles/even_parity.dir/clean

CMakeFiles/even_parity.dir/depend:
	cd /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity/cmake-build-debug /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity/cmake-build-debug /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-training/even-parity/cmake-build-debug/CMakeFiles/even_parity.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/even_parity.dir/depend

