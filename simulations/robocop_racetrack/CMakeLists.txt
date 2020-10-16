cmake_minimum_required(VERSION 2.8.3)
project(robocop_racetrack)

set(OpenCV_DIR /usr/share/OpenCV/)

## Generate added messages and services with any dependencies listed here
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  std_msgs
  tf
  cv_bridge
  image_transport
  OpenCV
)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES robocop_racetrack
 CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs std_msgs tf
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(
  ${PROJECT_NAME}_node 
  src/${PROJECT_NAME}_node.cpp 
  src/RobocopRacetrack.cpp
)

add_dependencies(
  ${PROJECT_NAME}_node 
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(
  ${PROJECT_NAME}_node 
  ${catkin_LIBRARIES}
)