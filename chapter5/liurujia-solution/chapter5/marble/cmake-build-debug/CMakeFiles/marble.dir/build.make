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
CMAKE_SOURCE_DIR = /home/fogsail/liurujia-solution/chapter5/marble

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fogsail/liurujia-solution/chapter5/marble/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/marble.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/marble.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/marble.dir/flags.make

CMakeFiles/marble.dir/main.cpp.o: CMakeFiles/marble.dir/flags.make
CMakeFiles/marble.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fogsail/liurujia-solution/chapter5/marble/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/marble.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/marble.dir/main.cpp.o -c /home/fogsail/liurujia-solution/chapter5/marble/main.cpp

CMakeFiles/marble.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/marble.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fogsail/liurujia-solution/chapter5/marble/main.cpp > CMakeFiles/marble.dir/main.cpp.i

CMakeFiles/marble.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/marble.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fogsail/liurujia-solution/chapter5/marble/main.cpp -o CMakeFiles/marble.dir/main.cpp.s

CMakeFiles/marble.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/marble.dir/main.cpp.o.requires

CMakeFiles/marble.dir/main.cpp.o.provides: CMakeFiles/marble.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/marble.dir/build.make CMakeFiles/marble.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/marble.dir/main.cpp.o.provides

CMakeFiles/marble.dir/main.cpp.o.provides.build: CMakeFiles/marble.dir/main.cpp.o


# Object files for target marble
marble_OBJECTS = \
"CMakeFiles/marble.dir/main.cpp.o"

# External object files for target marble
marble_EXTERNAL_OBJECTS =

marble: CMakeFiles/marble.dir/main.cpp.o
marble: CMakeFiles/marble.dir/build.make
marble: CMakeFiles/marble.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fogsail/liurujia-solution/chapter5/marble/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable marble"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/marble.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/marble.dir/build: marble

.PHONY : CMakeFiles/marble.dir/build

CMakeFiles/marble.dir/requires: CMakeFiles/marble.dir/main.cpp.o.requires

.PHONY : CMakeFiles/marble.dir/requires

CMakeFiles/marble.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/marble.dir/cmake_clean.cmake
.PHONY : CMakeFiles/marble.dir/clean

CMakeFiles/marble.dir/depend:
	cd /home/fogsail/liurujia-solution/chapter5/marble/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fogsail/liurujia-solution/chapter5/marble /home/fogsail/liurujia-solution/chapter5/marble /home/fogsail/liurujia-solution/chapter5/marble/cmake-build-debug /home/fogsail/liurujia-solution/chapter5/marble/cmake-build-debug /home/fogsail/liurujia-solution/chapter5/marble/cmake-build-debug/CMakeFiles/marble.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/marble.dir/depend

