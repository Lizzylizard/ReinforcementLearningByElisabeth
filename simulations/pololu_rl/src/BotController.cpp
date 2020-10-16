#include <pololu_rl/BotController.hpp>

BotController::BotController(ros::NodeHandle &nh) : nh_(nh)
{
    ROS_ASSERT(init());
}

BotController::~BotController() {}

bool BotController::init()
{
    BotImageHandler bih(nh_);
    BotSpeedHandler bsh(nh_);
    BotPoseHandler bph(nh_);

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
}