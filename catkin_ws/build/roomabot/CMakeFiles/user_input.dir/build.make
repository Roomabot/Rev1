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
CMAKE_SOURCE_DIR = /home/ubuntu/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/catkin_ws/build

# Include any dependencies generated for this target.
include roomabot/CMakeFiles/user_input.dir/depend.make

# Include the progress variables for this target.
include roomabot/CMakeFiles/user_input.dir/progress.make

# Include the compile flags for this target's objects.
include roomabot/CMakeFiles/user_input.dir/flags.make

roomabot/CMakeFiles/user_input.dir/src/user_input.cpp.o: roomabot/CMakeFiles/user_input.dir/flags.make
roomabot/CMakeFiles/user_input.dir/src/user_input.cpp.o: /home/ubuntu/catkin_ws/src/roomabot/src/user_input.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object roomabot/CMakeFiles/user_input.dir/src/user_input.cpp.o"
	cd /home/ubuntu/catkin_ws/build/roomabot && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/user_input.dir/src/user_input.cpp.o -c /home/ubuntu/catkin_ws/src/roomabot/src/user_input.cpp

roomabot/CMakeFiles/user_input.dir/src/user_input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/user_input.dir/src/user_input.cpp.i"
	cd /home/ubuntu/catkin_ws/build/roomabot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/catkin_ws/src/roomabot/src/user_input.cpp > CMakeFiles/user_input.dir/src/user_input.cpp.i

roomabot/CMakeFiles/user_input.dir/src/user_input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/user_input.dir/src/user_input.cpp.s"
	cd /home/ubuntu/catkin_ws/build/roomabot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/catkin_ws/src/roomabot/src/user_input.cpp -o CMakeFiles/user_input.dir/src/user_input.cpp.s

# Object files for target user_input
user_input_OBJECTS = \
"CMakeFiles/user_input.dir/src/user_input.cpp.o"

# External object files for target user_input
user_input_EXTERNAL_OBJECTS =

/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: roomabot/CMakeFiles/user_input.dir/src/user_input.cpp.o
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: roomabot/CMakeFiles/user_input.dir/build.make
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/libtf2_ros.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/libactionlib.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/libmessage_filters.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/libroscpp.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /usr/lib/aarch64-linux-gnu/libpthread.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /usr/lib/aarch64-linux-gnu/libboost_chrono.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /usr/lib/aarch64-linux-gnu/libboost_filesystem.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/librosconsole.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /usr/lib/aarch64-linux-gnu/liblog4cxx.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /usr/lib/aarch64-linux-gnu/libboost_regex.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/libtf2.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/librostime.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /usr/lib/aarch64-linux-gnu/libboost_date_time.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /opt/ros/noetic/lib/libcpp_common.so
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /usr/lib/aarch64-linux-gnu/libboost_system.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /usr/lib/aarch64-linux-gnu/libboost_thread.so.1.71.0
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: /usr/lib/aarch64-linux-gnu/libconsole_bridge.so.0.4
/home/ubuntu/catkin_ws/devel/lib/roomabot/user_input: roomabot/CMakeFiles/user_input.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/ubuntu/catkin_ws/devel/lib/roomabot/user_input"
	cd /home/ubuntu/catkin_ws/build/roomabot && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/user_input.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
roomabot/CMakeFiles/user_input.dir/build: /home/ubuntu/catkin_ws/devel/lib/roomabot/user_input

.PHONY : roomabot/CMakeFiles/user_input.dir/build

roomabot/CMakeFiles/user_input.dir/clean:
	cd /home/ubuntu/catkin_ws/build/roomabot && $(CMAKE_COMMAND) -P CMakeFiles/user_input.dir/cmake_clean.cmake
.PHONY : roomabot/CMakeFiles/user_input.dir/clean

roomabot/CMakeFiles/user_input.dir/depend:
	cd /home/ubuntu/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/catkin_ws/src /home/ubuntu/catkin_ws/src/roomabot /home/ubuntu/catkin_ws/build /home/ubuntu/catkin_ws/build/roomabot /home/ubuntu/catkin_ws/build/roomabot/CMakeFiles/user_input.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : roomabot/CMakeFiles/user_input.dir/depend

