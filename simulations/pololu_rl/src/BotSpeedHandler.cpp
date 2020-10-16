#include <pololu_rl/BotSpeedHandler.hpp>

BotSpeedHandler::BotSpeedHandler(ros::NodeHandle &nh) : nh_(nh)
{
    init();
}

BotSpeedHandler::~BotSpeedHandler() {}

void BotSpeedHandler::init()
{
    joy_speed_sub_ = nh_.subscribe("/joy", 1, &BotSpeedHandler::joyCallback, this);
    env__sub_ = nh_.subscribe("/env", 1, &BotSpeedHandler::envCallback, this);
    cmd_vel_ = nh_.advertise<my_msgs::VelJoint>("/cmd_vel", 1);
    reset_pos_srv_ = nh_.serviceClient<std_srvs::Empty>("/gazebo/reset_world");
}

void BotSpeedHandler::joyCallback(const sensor_msgs::Joy::ConstPtr &joy_msg)
{
    float left = joy_msg->axes[0] / 250 * 5;
    float right = joy_msg->axes[1] / 250 * 5;

    my_msgs::VelJoint wheel_speed;
    wheel_speed.left_vel = left;
    wheel_speed.right_vel = right;

    cmd_vel_.publish(wheel_speed);
}
void BotSpeedHandler::envCallback(const std_msgs::String::ConstPtr &env_msg)
{
    // ROS_WARN("bot = %s", env_msg->data.c_str());
    std_srvs::Empty srv_call;
    reset_pos_srv_.call(srv_call);
}