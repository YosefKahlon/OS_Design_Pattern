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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OS_Design_Pattern.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OS_Design_Pattern.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OS_Design_Pattern.dir/flags.make

CMakeFiles/OS_Design_Pattern.dir/main1.c.o: CMakeFiles/OS_Design_Pattern.dir/flags.make
CMakeFiles/OS_Design_Pattern.dir/main1.c.o: ../main1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OS_Design_Pattern.dir/main1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS_Design_Pattern.dir/main1.c.o   -c /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/main1.c

CMakeFiles/OS_Design_Pattern.dir/main1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS_Design_Pattern.dir/main1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/main1.c > CMakeFiles/OS_Design_Pattern.dir/main1.c.i

CMakeFiles/OS_Design_Pattern.dir/main1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS_Design_Pattern.dir/main1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/main1.c -o CMakeFiles/OS_Design_Pattern.dir/main1.c.s

CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.o: CMakeFiles/OS_Design_Pattern.dir/flags.make
CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.o: ../Guard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.o -c /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/Guard.cpp

CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/Guard.cpp > CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.i

CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/Guard.cpp -o CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.s

CMakeFiles/OS_Design_Pattern.dir/client.c.o: CMakeFiles/OS_Design_Pattern.dir/flags.make
CMakeFiles/OS_Design_Pattern.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/OS_Design_Pattern.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS_Design_Pattern.dir/client.c.o   -c /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/client.c

CMakeFiles/OS_Design_Pattern.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS_Design_Pattern.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/client.c > CMakeFiles/OS_Design_Pattern.dir/client.c.i

CMakeFiles/OS_Design_Pattern.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS_Design_Pattern.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/client.c -o CMakeFiles/OS_Design_Pattern.dir/client.c.s

CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.o: CMakeFiles/OS_Design_Pattern.dir/flags.make
CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.o: ../singleton.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.o -c /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/singleton.cpp

CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/singleton.cpp > CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.i

CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/singleton.cpp -o CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.s

# Object files for target OS_Design_Pattern
OS_Design_Pattern_OBJECTS = \
"CMakeFiles/OS_Design_Pattern.dir/main1.c.o" \
"CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.o" \
"CMakeFiles/OS_Design_Pattern.dir/client.c.o" \
"CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.o"

# External object files for target OS_Design_Pattern
OS_Design_Pattern_EXTERNAL_OBJECTS =

OS_Design_Pattern: CMakeFiles/OS_Design_Pattern.dir/main1.c.o
OS_Design_Pattern: CMakeFiles/OS_Design_Pattern.dir/Guard.cpp.o
OS_Design_Pattern: CMakeFiles/OS_Design_Pattern.dir/client.c.o
OS_Design_Pattern: CMakeFiles/OS_Design_Pattern.dir/singleton.cpp.o
OS_Design_Pattern: CMakeFiles/OS_Design_Pattern.dir/build.make
OS_Design_Pattern: CMakeFiles/OS_Design_Pattern.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable OS_Design_Pattern"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OS_Design_Pattern.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OS_Design_Pattern.dir/build: OS_Design_Pattern

.PHONY : CMakeFiles/OS_Design_Pattern.dir/build

CMakeFiles/OS_Design_Pattern.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OS_Design_Pattern.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OS_Design_Pattern.dir/clean

CMakeFiles/OS_Design_Pattern.dir/depend:
	cd /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/cmake-build-debug /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/cmake-build-debug /mnt/c/Users/97252/Documents/GitHub/OS_Design_Pattern/cmake-build-debug/CMakeFiles/OS_Design_Pattern.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OS_Design_Pattern.dir/depend

