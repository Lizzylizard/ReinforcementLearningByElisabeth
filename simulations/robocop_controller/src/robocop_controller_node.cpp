#include <ros/ros.h>
#include <robocop_controller/RobocopController.hpp>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "robocop_controller");
  ros::NodeHandle nh("~");
  RobocopController robocopController(nh);
}