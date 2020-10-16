#pragma once

#include <ros/ros.h>
#include <pololu_rl/BotImageHandler.hpp>
#include <pololu_rl/BotSpeedHandler.hpp>
#include <pololu_rl/BotPoseHandler.hpp>

class BotController
{
private:
    ros::NodeHandle &nh_;
    bool init();

public:
    BotController(ros::NodeHandle &nh);
    ~BotController();
};