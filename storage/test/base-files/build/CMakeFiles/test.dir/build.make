# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/serg/github/cloud/storage/test/base-files

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/serg/github/cloud/storage/test/base-files/build

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/main.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/serg/github/cloud/storage/test/base-files/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/main.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/main.cpp.o -c /home/serg/github/cloud/storage/test/base-files/main.cpp

CMakeFiles/test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/main.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/serg/github/cloud/storage/test/base-files/main.cpp > CMakeFiles/test.dir/main.cpp.i

CMakeFiles/test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/main.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/serg/github/cloud/storage/test/base-files/main.cpp -o CMakeFiles/test.dir/main.cpp.s

CMakeFiles/test.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/test.dir/main.cpp.o.requires

CMakeFiles/test.dir/main.cpp.o.provides: CMakeFiles/test.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/test.dir/main.cpp.o.provides

CMakeFiles/test.dir/main.cpp.o.provides.build: CMakeFiles/test.dir/main.cpp.o


CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o: /home/serg/github/cloud/storage/base.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/serg/github/cloud/storage/test/base-files/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o -c /home/serg/github/cloud/storage/base.cpp

CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/serg/github/cloud/storage/base.cpp > CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.i

CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/serg/github/cloud/storage/base.cpp -o CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.s

CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o.requires:

.PHONY : CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o.requires

CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o.provides: CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o.provides.build
.PHONY : CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o.provides

CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o.provides.build: CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o


# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/main.cpp.o" \
"CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test: CMakeFiles/test.dir/main.cpp.o
test: CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o
test: CMakeFiles/test.dir/build.make
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/serg/github/cloud/storage/test/base-files/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test

.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/requires: CMakeFiles/test.dir/main.cpp.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/home/serg/github/cloud/storage/base.cpp.o.requires

.PHONY : CMakeFiles/test.dir/requires

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /home/serg/github/cloud/storage/test/base-files/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/serg/github/cloud/storage/test/base-files /home/serg/github/cloud/storage/test/base-files /home/serg/github/cloud/storage/test/base-files/build /home/serg/github/cloud/storage/test/base-files/build /home/serg/github/cloud/storage/test/base-files/build/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend
