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
CMAKE_SOURCE_DIR = /home/fogsail/liurujia-solution/chapter5/Unix-ls

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fogsail/liurujia-solution/chapter5/Unix-ls/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Unix_ls.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Unix_ls.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Unix_ls.dir/flags.make

CMakeFiles/Unix_ls.dir/main.cpp.o: CMakeFiles/Unix_ls.dir/flags.make
CMakeFiles/Unix_ls.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fogsail/liurujia-solution/chapter5/Unix-ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Unix_ls.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Unix_ls.dir/main.cpp.o -c /home/fogsail/liurujia-solution/chapter5/Unix-ls/main.cpp

CMakeFiles/Unix_ls.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Unix_ls.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fogsail/liurujia-solution/chapter5/Unix-ls/main.cpp > CMakeFiles/Unix_ls.dir/main.cpp.i

CMakeFiles/Unix_ls.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Unix_ls.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fogsail/liurujia-solution/chapter5/Unix-ls/main.cpp -o CMakeFiles/Unix_ls.dir/main.cpp.s

CMakeFiles/Unix_ls.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Unix_ls.dir/main.cpp.o.requires

CMakeFiles/Unix_ls.dir/main.cpp.o.provides: CMakeFiles/Unix_ls.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Unix_ls.dir/build.make CMakeFiles/Unix_ls.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Unix_ls.dir/main.cpp.o.provides

CMakeFiles/Unix_ls.dir/main.cpp.o.provides.build: CMakeFiles/Unix_ls.dir/main.cpp.o


# Object files for target Unix_ls
Unix_ls_OBJECTS = \
"CMakeFiles/Unix_ls.dir/main.cpp.o"

# External object files for target Unix_ls
Unix_ls_EXTERNAL_OBJECTS =

Unix_ls: CMakeFiles/Unix_ls.dir/main.cpp.o
Unix_ls: CMakeFiles/Unix_ls.dir/build.make
Unix_ls: CMakeFiles/Unix_ls.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fogsail/liurujia-solution/chapter5/Unix-ls/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Unix_ls"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Unix_ls.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Unix_ls.dir/build: Unix_ls

.PHONY : CMakeFiles/Unix_ls.dir/build

CMakeFiles/Unix_ls.dir/requires: CMakeFiles/Unix_ls.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Unix_ls.dir/requires

CMakeFiles/Unix_ls.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Unix_ls.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Unix_ls.dir/clean

CMakeFiles/Unix_ls.dir/depend:
	cd /home/fogsail/liurujia-solution/chapter5/Unix-ls/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fogsail/liurujia-solution/chapter5/Unix-ls /home/fogsail/liurujia-solution/chapter5/Unix-ls /home/fogsail/liurujia-solution/chapter5/Unix-ls/cmake-build-debug /home/fogsail/liurujia-solution/chapter5/Unix-ls/cmake-build-debug /home/fogsail/liurujia-solution/chapter5/Unix-ls/cmake-build-debug/CMakeFiles/Unix_ls.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Unix_ls.dir/depend
