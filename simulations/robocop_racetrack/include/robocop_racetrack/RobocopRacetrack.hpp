#pragma once

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float64.h>
#include <std_msgs/UInt8.h>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>

#define MOV_AVG_LENGTH 5

class RobocopRacetrack
{
private:
  // ROS NodeHandle
  ros::NodeHandle &nh_;
  image_transport::ImageTransport it_;

  //   Topic publishers
  ros::Publisher cmd_vel_pub_;
  ros::Publisher line_reliability_pub_;
  ros::Publisher pid_set_point_pub_;
  ros::Publisher pid_state_pub_;

  // Topic subscribers
  image_transport::Subscriber image_raw_sub_;
  ros::Subscriber cmd_vel_sub_;
  ros::Subscriber pid_control_effort_sub_;

  // Initializer
  bool init();

  // Variables
  geometry_msgs::Twist twist_msg_;
  double effort_value_;

  // Images
  void imageCallback(const sensor_msgs::Image::ConstPtr &image_msg);

  //   Twist
  void velocityUpdate(double cx, double width);
  void stopMoving();

  // Effort
  void effortCallback(const std_msgs::Float64::ConstPtr &effort_msg);

  // Lane
  cv::Mat maskLane(cv::Mat cv_image);
  void laneCenter(cv::Mat masked_lane, cv::Mat cv_image);

public:
  RobocopRacetrack(ros::NodeHandle &nh);
  ~RobocopRacetrack();
};