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
CMAKE_SOURCE_DIR = /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/typical_homework.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/typical_homework.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/typical_homework.dir/flags.make

CMakeFiles/typical_homework.dir/main.cpp.o: CMakeFiles/typical_homework.dir/flags.make
CMakeFiles/typical_homework.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/typical_homework.dir/main.cpp.o"
	/usr/local/Cellar/gcc@6/6.4.0_2/bin/g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/typical_homework.dir/main.cpp.o -c /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework/main.cpp

CMakeFiles/typical_homework.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/typical_homework.dir/main.cpp.i"
	/usr/local/Cellar/gcc@6/6.4.0_2/bin/g++-6 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework/main.cpp > CMakeFiles/typical_homework.dir/main.cpp.i

CMakeFiles/typical_homework.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/typical_homework.dir/main.cpp.s"
	/usr/local/Cellar/gcc@6/6.4.0_2/bin/g++-6 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework/main.cpp -o CMakeFiles/typical_homework.dir/main.cpp.s

CMakeFiles/typical_homework.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/typical_homework.dir/main.cpp.o.requires

CMakeFiles/typical_homework.dir/main.cpp.o.provides: CMakeFiles/typical_homework.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/typical_homework.dir/build.make CMakeFiles/typical_homework.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/typical_homework.dir/main.cpp.o.provides

CMakeFiles/typical_homework.dir/main.cpp.o.provides.build: CMakeFiles/typical_homework.dir/main.cpp.o


# Object files for target typical_homework
typical_homework_OBJECTS = \
"CMakeFiles/typical_homework.dir/main.cpp.o"

# External object files for target typical_homework
typical_homework_EXTERNAL_OBJECTS =

typical_homework: CMakeFiles/typical_homework.dir/main.cpp.o
typical_homework: CMakeFiles/typical_homework.dir/build.make
typical_homework: CMakeFiles/typical_homework.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable typical_homework"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/typical_homework.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/typical_homework.dir/build: typical_homework

.PHONY : CMakeFiles/typical_homework.dir/build

CMakeFiles/typical_homework.dir/requires: CMakeFiles/typical_homework.dir/main.cpp.o.requires

.PHONY : CMakeFiles/typical_homework.dir/requires

CMakeFiles/typical_homework.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/typical_homework.dir/cmake_clean.cmake
.PHONY : CMakeFiles/typical_homework.dir/clean

CMakeFiles/typical_homework.dir/depend:
	cd /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework/cmake-build-debug /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework/cmake-build-debug /Users/zhangminchen/Downloads/research/solution-to-liurujia/ch4-practice/typical-homework/cmake-build-debug/CMakeFiles/typical_homework.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/typical_homework.dir/depend

