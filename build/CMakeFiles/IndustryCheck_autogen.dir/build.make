# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Meco\IndustryCheck

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Meco\IndustryCheck\build

# Utility rule file for IndustryCheck_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/IndustryCheck_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/IndustryCheck_autogen.dir/progress.make

CMakeFiles/IndustryCheck_autogen: IndustryCheck_autogen/timestamp

IndustryCheck_autogen/timestamp: C:/Qt/6.7.2/mingw_64/./bin/moc.exe
IndustryCheck_autogen/timestamp: C:/Qt/6.7.2/mingw_64/./bin/uic.exe
IndustryCheck_autogen/timestamp: CMakeFiles/IndustryCheck_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:\Meco\IndustryCheck\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target IndustryCheck"
	C:\cmake\bin\cmake.exe -E cmake_autogen C:/Meco/IndustryCheck/build/CMakeFiles/IndustryCheck_autogen.dir/AutogenInfo.json Debug
	C:\cmake\bin\cmake.exe -E touch C:/Meco/IndustryCheck/build/IndustryCheck_autogen/timestamp

IndustryCheck_autogen: CMakeFiles/IndustryCheck_autogen
IndustryCheck_autogen: IndustryCheck_autogen/timestamp
IndustryCheck_autogen: CMakeFiles/IndustryCheck_autogen.dir/build.make
.PHONY : IndustryCheck_autogen

# Rule to build all files generated by this target.
CMakeFiles/IndustryCheck_autogen.dir/build: IndustryCheck_autogen
.PHONY : CMakeFiles/IndustryCheck_autogen.dir/build

CMakeFiles/IndustryCheck_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\IndustryCheck_autogen.dir\cmake_clean.cmake
.PHONY : CMakeFiles/IndustryCheck_autogen.dir/clean

CMakeFiles/IndustryCheck_autogen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Meco\IndustryCheck C:\Meco\IndustryCheck C:\Meco\IndustryCheck\build C:\Meco\IndustryCheck\build C:\Meco\IndustryCheck\build\CMakeFiles\IndustryCheck_autogen.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/IndustryCheck_autogen.dir/depend
