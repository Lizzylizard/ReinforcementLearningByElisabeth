cmake_minimum_required(VERSION 2.8.3)
project(move_turtlebot_3)

find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  geometry_msgs
  roscpp
  std_msgs
)


## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  nav_msgs
  std_msgs
  geometry_msgs
)

## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
 LIBRARIES move_turtlebot_3
 CATKIN_DEPENDS nav_msgs roscpp std_msgs geometry_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(drivebot src/drivebot.cpp)
add_dependencies(drivebot ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(drivebot
  ${catkin_LIBRARIES}
)