#pragma once

#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>

#define DEG2RAD (M_PI / 180.0)

#define LINEAR_VELOCITY_X 0.3
#define ANGULAR_VELOCITY_Z 1.5
#define ZERO 0.0

#define DRIVE_FORWARD 0
#define TURN_RIGHT 1
#define TURN_LEFT 2

#define FCD 0.6
#define SCD 0.4

class RobocopController
{
private:
  // ROS NodeHandle
  ros::NodeHandle &nh_;

  //   Topic publishers
  ros::Publisher cmd_vel_pub_;
  ros::Publisher rc_image_raw_pub_;

  // Topic subscribers
  ros::Subscriber laser_scan_sub_;
  ros::Subscriber image_raw_sub_;

  // Variables
  double current_pose_;

  // Initializer
  bool init();

  //   Function prototypes
  //   Laser scan
  void laserCallback(const sensor_msgs::LaserScan::ConstPtr &laser_msg);
  double scanToRegion(std::vector<float> arr, int lowerbound, int upperbound,
                      double range_max);  // Break scan into 5 regions
  void coliisionAvoidance(std::map<std::string, double> region);

  // Odometry
  void odomMsgCallback(const nav_msgs::Odometry::ConstPtr &odom_msg);

  //   Twist
  void velocityUpdate(double linear_x, double angular_z);
  void drive(int direction);

  // Images
  void imageCallback(const sensor_msgs::Image::ConstPtr &image_msg);

public:
  RobocopController(ros::NodeHandle &nh);
  ~RobocopController();
};
