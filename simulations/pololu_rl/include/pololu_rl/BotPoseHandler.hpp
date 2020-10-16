#pragma once

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/String.h>
#include <sstream>

class BotPoseHandler
{
private:
    ros::NodeHandle &nh_;
    ros::Subscriber pose_sub_;
    ros::Publisher pose_pub_;

    void init();
    void odomCallback(const nav_msgs::Odometry::ConstPtr &pose_msg);
    bool is_between(std::pair<float, float> a, std::pair<float, float> b, std::pair<float, float> c);

public:
    BotPoseHandler(ros::NodeHandle &nh);
    ~BotPoseHandler();
};
