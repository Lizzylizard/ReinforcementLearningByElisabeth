#include <ros/ros.h>
#include <robocop_controller/RobocopController.hpp>

RobocopController::RobocopController(ros::NodeHandle &nh) : nh_(nh)
{
  ROS_INFO("Robocop controller started");
  ROS_ASSERT(init());
}

RobocopController::~RobocopController()
{
  velocityUpdate(0.0, 0.0);
  ros::shutdown();
}

// Initializer
bool RobocopController::init()
{
  // Initialize variables
  current_pose_ = 0.0;

  // Initialize publishers
  cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  rc_image_raw_pub_ = nh_.advertise<sensor_msgs::Image>("/rc_image_raw", 1);

  // Initialize subscribers
  laser_scan_sub_ = nh_.subscribe("/scan", 1, &RobocopController::laserCallback, this);
  image_raw_sub_ = nh_.subscribe("/camera/rgb/image_raw", 1, &RobocopController::imageCallback, this);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
}

// Laser scan
void RobocopController::laserCallback(const sensor_msgs::LaserScan::ConstPtr &laser_msg)
{
  std::map<std::string, double> region;
  region["fright"] = scanToRegion(laser_msg->ranges, 144, 287, laser_msg->range_max);
  region["front"] = scanToRegion(laser_msg->ranges, 288, 431, laser_msg->range_max);
  region["fleft"] = scanToRegion(laser_msg->ranges, 432, 575, laser_msg->range_max);

  coliisionAvoidance(region);
}

// Scan to region
double RobocopController::scanToRegion(std::vector<float> arr, int lowerbound, int upperbound, double range_max)
{
  std::vector<double> temp_array;
  double region;

  for (int i = lowerbound; i <= upperbound; i++)
  {
    temp_array.push_back(arr[i]);
  }

  region = *std::min_element(temp_array.begin(), temp_array.end());

  if (std::isinf(region))
    return range_max;
  else
    return region;
}

// Collison avoidance
void RobocopController::coliisionAvoidance(std::map<std::string, double> region)
{
  // ROS_INFO("[%f, %f, %f]", region["front"], region["fleft"],
  // region["fright"]);

  if (region["front"] > FCD)
  {
    if (region["fright"] < SCD)
    {
      ROS_INFO("front clear but right blocked, turning left");
      drive(TURN_LEFT);
    }
    else if (region["fleft"] < SCD)
    {
      ROS_INFO("front clear but left blocked, turning right");
      drive(TURN_RIGHT);
    }

    else
    {
      ROS_INFO("drive forward");
      drive(DRIVE_FORWARD);
    }
  }

  if (region["front"] < FCD)
  {
    if (region["fright"] < SCD)
    {
      ROS_INFO("front and right blocked, turning left");
      drive(TURN_LEFT);
    }
    else if (region["fleft"] < SCD)
    {
      ROS_INFO("front and left blocked, turning right");
      drive(TURN_RIGHT);
    }
    else
    {
      if (region["fleft"] < region["fright"])
      {
        ROS_INFO("front and left blocked with space on right, turning right");
        drive(TURN_RIGHT);
      }
      else
      {
        ROS_INFO("front and right blocked with space on left, turning left");
        drive(TURN_LEFT);
      }
    }
  }
}

// Odometry
void RobocopController::odomMsgCallback(const nav_msgs::Odometry::ConstPtr &odom_msg)
{
  double siny = 2.0 * (odom_msg->pose.pose.orientation.w * odom_msg->pose.pose.orientation.z +
                       odom_msg->pose.pose.orientation.x * odom_msg->pose.pose.orientation.y);
  double cosy = 1.0 - 2.0 * (odom_msg->pose.pose.orientation.y * odom_msg->pose.pose.orientation.y +
                             odom_msg->pose.pose.orientation.z * odom_msg->pose.pose.orientation.z);

  current_pose_ = atan2(siny, cosy);
}

// Twist
void RobocopController::velocityUpdate(double linear_x, double angular_z)
{
  geometry_msgs::Twist twist_msg;

  twist_msg.linear.x = linear_x;
  twist_msg.angular.z = angular_z;

  cmd_vel_pub_.publish(twist_msg);
}

//  Drive
void RobocopController::drive(int direction)
{
  switch (direction)
  {
    case DRIVE_FORWARD:
      velocityUpdate(LINEAR_VELOCITY_X, ZERO);
      break;

    case TURN_RIGHT:
      velocityUpdate(ZERO, -1 * ANGULAR_VELOCITY_Z);
      break;

    case TURN_LEFT:
      velocityUpdate(ZERO, ANGULAR_VELOCITY_Z);
      break;

    default:
      velocityUpdate(ZERO, ZERO);
      break;
  }
}

// Camera
void RobocopController::imageCallback(const sensor_msgs::Image::ConstPtr &image_msg)
{
  sensor_msgs::Image image_msg_pub;

  image_msg_pub.header.seq = image_msg->header.seq;
  image_msg_pub.header.stamp = image_msg->header.stamp;
  image_msg_pub.header.frame_id = image_msg->header.frame_id;
  image_msg_pub.height = image_msg->height;
  image_msg_pub.width = image_msg->width;
  image_msg_pub.encoding = image_msg->encoding;
  image_msg_pub.is_bigendian = image_msg->is_bigendian;
  image_msg_pub.step = image_msg->step;
  image_msg_pub.data = image_msg->data;

  rc_image_raw_pub_.publish(image_msg_pub);
}
