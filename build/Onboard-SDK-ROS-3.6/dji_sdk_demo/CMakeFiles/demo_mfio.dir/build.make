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
CMAKE_SOURCE_DIR = /home/ivica/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivica/catkin_ws/build

# Include any dependencies generated for this target.
include Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/depend.make

# Include the progress variables for this target.
include Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/progress.make

# Include the compile flags for this target's objects.
include Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/flags.make

Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o: Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/flags.make
Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o: /home/ivica/catkin_ws/src/Onboard-SDK-ROS-3.6/dji_sdk_demo/src/demo_mfio.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivica/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o"
	cd /home/ivica/catkin_ws/build/Onboard-SDK-ROS-3.6/dji_sdk_demo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o -c /home/ivica/catkin_ws/src/Onboard-SDK-ROS-3.6/dji_sdk_demo/src/demo_mfio.cpp

Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.i"
	cd /home/ivica/catkin_ws/build/Onboard-SDK-ROS-3.6/dji_sdk_demo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivica/catkin_ws/src/Onboard-SDK-ROS-3.6/dji_sdk_demo/src/demo_mfio.cpp > CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.i

Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.s"
	cd /home/ivica/catkin_ws/build/Onboard-SDK-ROS-3.6/dji_sdk_demo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivica/catkin_ws/src/Onboard-SDK-ROS-3.6/dji_sdk_demo/src/demo_mfio.cpp -o CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.s

Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o.requires:

.PHONY : Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o.requires

Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o.provides: Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o.requires
	$(MAKE) -f Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/build.make Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o.provides.build
.PHONY : Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o.provides

Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o.provides.build: Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o


# Object files for target demo_mfio
demo_mfio_OBJECTS = \
"CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o"

# External object files for target demo_mfio
demo_mfio_EXTERNAL_OBJECTS =

/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/build.make
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/libimage_transport.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/libmessage_filters.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libtinyxml2.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/libclass_loader.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/libPocoFoundation.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libdl.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/libroscpp.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/libroslib.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/librospack.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libpython2.7.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libtinyxml.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /home/ivica/catkin_ws/devel/lib/libcv_bridge.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_core3.so.3.3.1
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgproc3.so.3.3.1
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgcodecs3.so.3.3.1
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/librosconsole.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/librostime.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/libcpp_common.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /usr/local/lib/libdjiosdk-core.a
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgcodecs3.so.3.3.1
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgproc3.so.3.3.1
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_core3.so.3.3.1
/home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio: Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ivica/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio"
	cd /home/ivica/catkin_ws/build/Onboard-SDK-ROS-3.6/dji_sdk_demo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo_mfio.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/build: /home/ivica/catkin_ws/devel/lib/dji_sdk_demo/demo_mfio

.PHONY : Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/build

Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/requires: Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/src/demo_mfio.cpp.o.requires

.PHONY : Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/requires

Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/clean:
	cd /home/ivica/catkin_ws/build/Onboard-SDK-ROS-3.6/dji_sdk_demo && $(CMAKE_COMMAND) -P CMakeFiles/demo_mfio.dir/cmake_clean.cmake
.PHONY : Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/clean

Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/depend:
	cd /home/ivica/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivica/catkin_ws/src /home/ivica/catkin_ws/src/Onboard-SDK-ROS-3.6/dji_sdk_demo /home/ivica/catkin_ws/build /home/ivica/catkin_ws/build/Onboard-SDK-ROS-3.6/dji_sdk_demo /home/ivica/catkin_ws/build/Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Onboard-SDK-ROS-3.6/dji_sdk_demo/CMakeFiles/demo_mfio.dir/depend

