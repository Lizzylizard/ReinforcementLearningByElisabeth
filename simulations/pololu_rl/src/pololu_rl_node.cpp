#include <ros/ros.h>
#include <pololu_rl/BotController.hpp>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pololu_rl");
    ros::NodeHandle nh("~");

    BotController bc(nh);
}