# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug

# Include any dependencies generated for this target.
include common/CMakeFiles/LPS25HP.dir/depend.make

# Include the progress variables for this target.
include common/CMakeFiles/LPS25HP.dir/progress.make

# Include the compile flags for this target's objects.
include common/CMakeFiles/LPS25HP.dir/flags.make

common/CMakeFiles/LPS25HP.dir/LPS25HP.c.obj: common/CMakeFiles/LPS25HP.dir/flags.make
common/CMakeFiles/LPS25HP.dir/LPS25HP.c.obj: ../common/LPS25HP.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object common/CMakeFiles/LPS25HP.dir/LPS25HP.c.obj"
	cd /d C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug\common && C:\PROGRA~1\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\LPS25HP.dir\LPS25HP.c.obj   -c C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\common\LPS25HP.c

common/CMakeFiles/LPS25HP.dir/LPS25HP.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LPS25HP.dir/LPS25HP.c.i"
	cd /d C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug\common && C:\PROGRA~1\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\common\LPS25HP.c > CMakeFiles\LPS25HP.dir\LPS25HP.c.i

common/CMakeFiles/LPS25HP.dir/LPS25HP.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LPS25HP.dir/LPS25HP.c.s"
	cd /d C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug\common && C:\PROGRA~1\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\common\LPS25HP.c -o CMakeFiles\LPS25HP.dir\LPS25HP.c.s

# Object files for target LPS25HP
LPS25HP_OBJECTS = \
"CMakeFiles/LPS25HP.dir/LPS25HP.c.obj"

# External object files for target LPS25HP
LPS25HP_EXTERNAL_OBJECTS =

lib/libLPS25HP.a: common/CMakeFiles/LPS25HP.dir/LPS25HP.c.obj
lib/libLPS25HP.a: common/CMakeFiles/LPS25HP.dir/build.make
lib/libLPS25HP.a: common/CMakeFiles/LPS25HP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ..\lib\libLPS25HP.a"
	cd /d C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug\common && $(CMAKE_COMMAND) -P CMakeFiles\LPS25HP.dir\cmake_clean_target.cmake
	cd /d C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug\common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LPS25HP.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
common/CMakeFiles/LPS25HP.dir/build: lib/libLPS25HP.a

.PHONY : common/CMakeFiles/LPS25HP.dir/build

common/CMakeFiles/LPS25HP.dir/clean:
	cd /d C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug\common && $(CMAKE_COMMAND) -P CMakeFiles\LPS25HP.dir\cmake_clean.cmake
.PHONY : common/CMakeFiles/LPS25HP.dir/clean

common/CMakeFiles/LPS25HP.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\common C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug\common C:\Users\clemens\Desktop\G4_Themengebiet1_Holzer_Krenn_Haindl\cmake-build-debug\common\CMakeFiles\LPS25HP.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : common/CMakeFiles/LPS25HP.dir/depend

