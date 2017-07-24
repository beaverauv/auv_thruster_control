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


add_executable(thruster_control_node
  src/thruster_controller_node.cpp
  src/Axis.cpp
  src/Strafe.cpp
  src/Thrusters.cpp
)

add_executable(thruster_test_node
  src/thruster_test_node.cpp
)

target_link_libraries(thruster_control_node ${catkin_LIBRARIES})
target_link_libraries(thruster_test_node ${catkin_LIBRARIES})

add_dependencies(thruster_control_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
  auv_thruster_control_generate_messages_cpp
)
