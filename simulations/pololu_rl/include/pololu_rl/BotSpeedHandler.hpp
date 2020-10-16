#pragma once

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>
#include <std_srvs/Empty.h>
#include "my_msgs/VelJoint.h"

class BotSpeedHandler
{
private:
    ros::NodeHandle &nh_;
    ros::Subscriber joy_speed_sub_;
    ros::Subscriber env__sub_;
    ros::Publisher cmd_vel_;
    ros::ServiceClient reset_pos_srv_;

    void init();
    void joyCallback(const sensor_msgs::Joy::ConstPtr &joy_msg);
    void envCallback(const std_msgs::String::ConstPtr &env_msg);

public:
    BotSpeedHandler(ros::NodeHandle &nh);
    ~BotSpeedHandler();
};