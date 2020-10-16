#include <ros/ros.h>
#include <robocop_racetrack/RobocopRacetrack.hpp>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "robocop_racetrack");
  ros::NodeHandle nh("~");
  RobocopRacetrack robocopRacetrack(nh);
}