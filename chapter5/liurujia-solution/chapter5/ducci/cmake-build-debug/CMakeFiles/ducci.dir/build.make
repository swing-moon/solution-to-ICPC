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
CMAKE_SOURCE_DIR = /home/fogsail/liurujia-solution/chapter5/ducci

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fogsail/liurujia-solution/chapter5/ducci/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ducci.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ducci.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ducci.dir/flags.make

CMakeFiles/ducci.dir/main.cpp.o: CMakeFiles/ducci.dir/flags.make
CMakeFiles/ducci.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fogsail/liurujia-solution/chapter5/ducci/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ducci.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ducci.dir/main.cpp.o -c /home/fogsail/liurujia-solution/chapter5/ducci/main.cpp

CMakeFiles/ducci.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ducci.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fogsail/liurujia-solution/chapter5/ducci/main.cpp > CMakeFiles/ducci.dir/main.cpp.i

CMakeFiles/ducci.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ducci.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fogsail/liurujia-solution/chapter5/ducci/main.cpp -o CMakeFiles/ducci.dir/main.cpp.s

CMakeFiles/ducci.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ducci.dir/main.cpp.o.requires

CMakeFiles/ducci.dir/main.cpp.o.provides: CMakeFiles/ducci.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ducci.dir/build.make CMakeFiles/ducci.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ducci.dir/main.cpp.o.provides

CMakeFiles/ducci.dir/main.cpp.o.provides.build: CMakeFiles/ducci.dir/main.cpp.o


# Object files for target ducci
ducci_OBJECTS = \
"CMakeFiles/ducci.dir/main.cpp.o"

# External object files for target ducci
ducci_EXTERNAL_OBJECTS =

ducci: CMakeFiles/ducci.dir/main.cpp.o
ducci: CMakeFiles/ducci.dir/build.make
ducci: CMakeFiles/ducci.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fogsail/liurujia-solution/chapter5/ducci/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ducci"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ducci.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ducci.dir/build: ducci

.PHONY : CMakeFiles/ducci.dir/build

CMakeFiles/ducci.dir/requires: CMakeFiles/ducci.dir/main.cpp.o.requires

.PHONY : CMakeFiles/ducci.dir/requires

CMakeFiles/ducci.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ducci.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ducci.dir/clean

CMakeFiles/ducci.dir/depend:
	cd /home/fogsail/liurujia-solution/chapter5/ducci/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fogsail/liurujia-solution/chapter5/ducci /home/fogsail/liurujia-solution/chapter5/ducci /home/fogsail/liurujia-solution/chapter5/ducci/cmake-build-debug /home/fogsail/liurujia-solution/chapter5/ducci/cmake-build-debug /home/fogsail/liurujia-solution/chapter5/ducci/cmake-build-debug/CMakeFiles/ducci.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ducci.dir/depend
