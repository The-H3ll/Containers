# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /Users/molabhai/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Users/molabhai/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/molabhai/Desktop/Containers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/molabhai/Desktop/Containers/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Containers.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Containers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Containers.dir/flags.make

CMakeFiles/Containers.dir/main.cpp.o: CMakeFiles/Containers.dir/flags.make
CMakeFiles/Containers.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/molabhai/Desktop/Containers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Containers.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Containers.dir/main.cpp.o -c /Users/molabhai/Desktop/Containers/main.cpp

CMakeFiles/Containers.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Containers.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/molabhai/Desktop/Containers/main.cpp > CMakeFiles/Containers.dir/main.cpp.i

CMakeFiles/Containers.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Containers.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/molabhai/Desktop/Containers/main.cpp -o CMakeFiles/Containers.dir/main.cpp.s

CMakeFiles/Containers.dir/vector.cpp.o: CMakeFiles/Containers.dir/flags.make
CMakeFiles/Containers.dir/vector.cpp.o: ../vector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/molabhai/Desktop/Containers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Containers.dir/vector.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Containers.dir/vector.cpp.o -c /Users/molabhai/Desktop/Containers/vector.cpp

CMakeFiles/Containers.dir/vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Containers.dir/vector.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/molabhai/Desktop/Containers/vector.cpp > CMakeFiles/Containers.dir/vector.cpp.i

CMakeFiles/Containers.dir/vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Containers.dir/vector.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/molabhai/Desktop/Containers/vector.cpp -o CMakeFiles/Containers.dir/vector.cpp.s

# Object files for target Containers
Containers_OBJECTS = \
"CMakeFiles/Containers.dir/main.cpp.o" \
"CMakeFiles/Containers.dir/vector.cpp.o"

# External object files for target Containers
Containers_EXTERNAL_OBJECTS =

Containers: CMakeFiles/Containers.dir/main.cpp.o
Containers: CMakeFiles/Containers.dir/vector.cpp.o
Containers: CMakeFiles/Containers.dir/build.make
Containers: CMakeFiles/Containers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/molabhai/Desktop/Containers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Containers"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Containers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Containers.dir/build: Containers

.PHONY : CMakeFiles/Containers.dir/build

CMakeFiles/Containers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Containers.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Containers.dir/clean

CMakeFiles/Containers.dir/depend:
	cd /Users/molabhai/Desktop/Containers/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/molabhai/Desktop/Containers /Users/molabhai/Desktop/Containers /Users/molabhai/Desktop/Containers/cmake-build-debug /Users/molabhai/Desktop/Containers/cmake-build-debug /Users/molabhai/Desktop/Containers/cmake-build-debug/CMakeFiles/Containers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Containers.dir/depend
