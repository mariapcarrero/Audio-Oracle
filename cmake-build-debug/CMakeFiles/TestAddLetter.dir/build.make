# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TestAddLetter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TestAddLetter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestAddLetter.dir/flags.make

CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.o: CMakeFiles/TestAddLetter.dir/flags.make
CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.o: ../test_add_letter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.o -c /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle/test_add_letter.cpp

CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle/test_add_letter.cpp > CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.i

CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle/test_add_letter.cpp -o CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.s

# Object files for target TestAddLetter
TestAddLetter_OBJECTS = \
"CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.o"

# External object files for target TestAddLetter
TestAddLetter_EXTERNAL_OBJECTS =

TestAddLetter: CMakeFiles/TestAddLetter.dir/test_add_letter.cpp.o
TestAddLetter: CMakeFiles/TestAddLetter.dir/build.make
TestAddLetter: libFO.a
TestAddLetter: CMakeFiles/TestAddLetter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TestAddLetter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestAddLetter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestAddLetter.dir/build: TestAddLetter

.PHONY : CMakeFiles/TestAddLetter.dir/build

CMakeFiles/TestAddLetter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestAddLetter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestAddLetter.dir/clean

CMakeFiles/TestAddLetter.dir/depend:
	cd /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle/cmake-build-debug /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle/cmake-build-debug /Users/mariapaulacarrero/Documents/MARSYAS/Audio-Oracle/cmake-build-debug/CMakeFiles/TestAddLetter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestAddLetter.dir/depend
