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
CMAKE_COMMAND = /Users/doruk/opt/anaconda3/lib/python3.7/site-packages/cmake/data/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Users/doruk/opt/anaconda3/lib/python3.7/site-packages/cmake/data/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build

# Include any dependencies generated for this target.
include src/pango/CMakeFiles/projections.dir/depend.make

# Include the progress variables for this target.
include src/pango/CMakeFiles/projections.dir/progress.make

# Include the compile flags for this target's objects.
include src/pango/CMakeFiles/projections.dir/flags.make

src/pango/CMakeFiles/projections.dir/test5-proj.cpp.o: src/pango/CMakeFiles/projections.dir/flags.make
src/pango/CMakeFiles/projections.dir/test5-proj.cpp.o: ../src/pango/test5-proj.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/pango/CMakeFiles/projections.dir/test5-proj.cpp.o"
	cd /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build/src/pango && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/projections.dir/test5-proj.cpp.o -c /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/src/pango/test5-proj.cpp

src/pango/CMakeFiles/projections.dir/test5-proj.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/projections.dir/test5-proj.cpp.i"
	cd /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build/src/pango && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/src/pango/test5-proj.cpp > CMakeFiles/projections.dir/test5-proj.cpp.i

src/pango/CMakeFiles/projections.dir/test5-proj.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/projections.dir/test5-proj.cpp.s"
	cd /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build/src/pango && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/src/pango/test5-proj.cpp -o CMakeFiles/projections.dir/test5-proj.cpp.s

# Object files for target projections
projections_OBJECTS = \
"CMakeFiles/projections.dir/test5-proj.cpp.o"

# External object files for target projections
projections_EXTERNAL_OBJECTS =

../projections: src/pango/CMakeFiles/projections.dir/test5-proj.cpp.o
../projections: src/pango/CMakeFiles/projections.dir/build.make
../projections: libuwimg++.dylib
../projections: /Users/doruk/Documents/Projects/GitHub/Pangolin/build/src/libpangolin.dylib
../projections: /usr/local/lib/libGLEW.dylib
../projections: src/pango/CMakeFiles/projections.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../projections"
	cd /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build/src/pango && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/projections.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/pango/CMakeFiles/projections.dir/build: ../projections

.PHONY : src/pango/CMakeFiles/projections.dir/build

src/pango/CMakeFiles/projections.dir/clean:
	cd /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build/src/pango && $(CMAKE_COMMAND) -P CMakeFiles/projections.dir/cmake_clean.cmake
.PHONY : src/pango/CMakeFiles/projections.dir/clean

src/pango/CMakeFiles/projections.dir/depend:
	cd /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5 /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/src/pango /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build/src/pango /Users/doruk/Documents/Projects/GitHub/cse576_sp20_hw5/build/src/pango/CMakeFiles/projections.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/pango/CMakeFiles/projections.dir/depend

