#include <pololu_rl/BotPoseHandler.hpp>

BotPoseHandler::BotPoseHandler(ros::NodeHandle &nh) : nh_(nh)
{
    init();
}

BotPoseHandler::~BotPoseHandler()
{
}

void BotPoseHandler::init()
{
    pose_sub_ = nh_.subscribe("/odom", 1, &BotPoseHandler::odomCallback, this);
    pose_pub_ = nh_.advertise<std_msgs::String>("/position", 1);
}

void BotPoseHandler::odomCallback(const nav_msgs::Odometry::ConstPtr &pose_msg)
{
    float x = pose_msg->pose.pose.position.x;
    float y = pose_msg->pose.pose.position.y;

    std::stringstream ss;
    std_msgs::String msg;

    std::pair<float, float> bot_pose(x, y);

    std::pair<float, float> start_pose_a(-3.38, -6.225);
    std::pair<float, float> start_pose_b(-2.88, -6.225);

    std::pair<float, float> first_door_a(-2.03, -0.43);
    std::pair<float, float> first_door_b(-2.03, 0.07);

    std::pair<float, float> second_door_a(4.90, 3.1);
    std::pair<float, float> second_door_b(4.90, 3.6);

    std::pair<float, float> third_door_a(-6.44, 2.86);
    std::pair<float, float> third_door_b(-6.44, 2.36);

    std::pair<float, float> completed_pose_a(-3.5, -6.225);
    std::pair<float, float> completed_pose_b(-4.0, -6.225);

    if (is_between(start_pose_b, start_pose_a, bot_pose))
        ss << "start";

    else if (is_between(first_door_b, first_door_a, bot_pose))
        ss << "first";

    else if (is_between(second_door_b, second_door_a, bot_pose))
        ss << "second";

    else if (is_between(third_door_b, third_door_a, bot_pose))
        ss << "third";

    else if (is_between(completed_pose_b, completed_pose_a, bot_pose))
        ss << "completed";

    else
        ss << "unknown";

    msg.data = ss.str();
    pose_pub_.publish(msg);
}

bool BotPoseHandler::is_between(std::pair<float, float> a, std::pair<float, float> b, std::pair<float, float> c)
{
    float cross_product = (c.second - a.second) * (b.first - a.first) - (c.first - a.first) * (b.second - a.second);

    if (abs(cross_product) > std::numeric_limits<double>::epsilon())
        return false;

    float dot_product = (c.first - a.first) * (b.first - a.first) + (c.second - a.second) * (b.second - a.second);

    if (dot_product < 0)
        return false;

    float squared_lengths_ba = (b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second);

    if (dot_product > squared_lengths_ba)
        return false;

    return true;
}