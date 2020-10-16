cmake_minimum_required(VERSION 2.8.3)
project(pololu_rl)

set(OpenCV_DIR /usr/local/lib/cmake/opencv4/)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  OpenCV
  cv_bridge
  geometry_msgs
  image_transport
  roscpp
  sensor_msgs
  std_msgs
  nav_msgs
  tf
  my_msgs
  std_srvs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
 INCLUDE_DIRS include
 LIBRARIES pololu_rl_new
 CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs std_msgs nav_msgs tf std_srvs
#  DEPENDS system_lib
)

###########
## Build ##
###########
include_directories(
include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(
  ${PROJECT_NAME}_node 
  src/${PROJECT_NAME}_node.cpp 
  src/BotController.cpp 
  src/BotImageHandler.cpp
  src/BotSpeedHandler.cpp
  src/BotPoseHandler.cpp
)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(
  ${PROJECT_NAME}_node 
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

## Specify libraries to link a library or executable target against
target_link_libraries(
  ${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)