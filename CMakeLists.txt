cmake_minimum_required(VERSION 2.8.3)

project(auv_thruster_control)


add_definitions("-std=c++14")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)


add_message_files(
   FILES
   Thrust.msg
   ThrustStamped.msg
 )

generate_messages(
   DEPENDENCIES
   std_msgs
 )


catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS message_runtime
)


## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  include/
)


add_executable(thrust_control_cont
  src/thruster_controller_node.cpp
  src/Axis.cpp
  src/Strafe.cpp
  src/Thrusters.cpp
)

target_link_libraries(thrust_control_cont ${catkin_LIBRARIES})
add_dependencies(thrust_control_cont
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
  auv_thruster_control_generate_messages_cpp
)
