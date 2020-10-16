#include <robocop_racetrack/RobocopRacetrack.hpp>

RobocopRacetrack::RobocopRacetrack(ros::NodeHandle &nh) : nh_(nh), it_(nh)
{
  ROS_INFO("Robocop racetrack started");
  ROS_ASSERT(init());
}

RobocopRacetrack::~RobocopRacetrack()
{
  stopMoving();
  ros::shutdown();
}

// Initializer
bool RobocopRacetrack::init()
{
  // Initialize variables
  effort_value_ = 0;
  // Initialize publishersers
  cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  pid_set_point_pub_ = nh_.advertise<std_msgs::Float64>("/setpoint", 1);
  pid_state_pub_ = nh_.advertise<std_msgs::Float64>("/state", 1);

  // Initialize subscribers
  image_raw_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &RobocopRacetrack::imageCallback, this);
  pid_control_effort_sub_ = nh_.subscribe("/control_effort", 1, &RobocopRacetrack::effortCallback, this);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
}

// Camera
void RobocopRacetrack::imageCallback(const sensor_msgs::Image::ConstPtr &image_msg)
{
  cv_bridge::CvImagePtr cv_bridge_image;
  cv::Mat cv_image, blured_img, masked_lane;

  try
  {
    cv_bridge_image = cv_bridge::toCvCopy(image_msg, sensor_msgs::image_encodings::BGR8);
  }
  catch (const cv_bridge::Exception &e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  cv_image = cv_bridge_image->image;
  cv::pyrDown(cv_image, cv_image);
  cv::GaussianBlur(cv_image, blured_img, cv::Size(7, 7), 3, 3);

  masked_lane = maskLane(blured_img);
  laneCenter(masked_lane, cv_image);

  cv::imshow("original view", cv_image);
  cv::imshow("blurred view", blured_img);
  cv::imshow("result", masked_lane);
  cv::waitKey(3);
}

// Mask lane
cv::Mat RobocopRacetrack::maskLane(cv::Mat cv_image)
{
  int hue_l, hue_h, saturation_l, saturation_h, lightness_l, lightness_h;

  cv::Mat hsv, mask, result;

  // convert image to hsv
  cv::cvtColor(cv_image, hsv, cv::COLOR_BGR2HSV);

  hue_l = 0;
  hue_h = 0;
  saturation_l = 0;
  saturation_h = 0;
  lightness_l = 0;
  lightness_h = 50;

  // define range of color
  cv::Scalar lower_color = cv::Scalar(hue_l, saturation_l, lightness_l);
  cv::Scalar upper_color = cv::Scalar(hue_h, saturation_h, lightness_h);

  // threshold the hsv image to get desired color
  cv::inRange(hsv, lower_color, upper_color, mask);

  // bitwise and mask the original image
  cv::bitwise_and(hsv, hsv, result, mask);

  return mask;
}

// Lane center
void RobocopRacetrack::laneCenter(cv::Mat masked_lane, cv::Mat cv_image)
{
  cv::Mat canny_output;
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;

  cv::findContours(masked_lane, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_L1, cv::Point(0, 0));

  std::vector<cv::Moments> mu(contours.size());
  std::vector<cv::Point2f> mc(contours.size());

  for (int i = 0; i < contours.size(); i++)
  {
    mu[i] = cv::moments(contours[i], false);
    mc[i] = cv::Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
    cv::circle(cv_image, mc[i], 7, cv::Scalar(0, 0, 255), -1);
  }

  int most_right_centroid_index, index, max_x_index = 0;
  double cx, cy;

  if (mc.size() > 0)
  {
    for (auto const &location : mc)
    {
      cx = location.x;

      if (cx >= max_x_index)
      {
        max_x_index = cx;
        most_right_centroid_index = index;
      }
      index += 1;
    }

    try
    {
      cx = mc[most_right_centroid_index].x;
      cy = mc[most_right_centroid_index].y;
    }
    catch (const std::exception &e)
    {
      cx = cv_image.size().height / 2;
      cy = cv_image.size().width / 2;
    }
  }
  else
  {
    cx = cv_image.size().height / 2;
    cy = cv_image.size().width / 2;
  }

  cv::circle(cv_image, cv::Point(cx, cy), 7, cv::Scalar(0, 255, 0), -1);

  velocityUpdate(cx, cy);
}

// Twist
void RobocopRacetrack::velocityUpdate(double cx, double width)
{
  std_msgs::Float64 point_msg;
  std_msgs::Float64 state_msg;

  // without pid
  double error_x = cx - width / 1.5;
  double angular_z = -error_x / 100;

  if (abs(angular_z) < 0.09)
    twist_msg_.linear.x = 0.35;
  else
    twist_msg_.linear.x = 0.2;
  twist_msg_.angular.z = angular_z;

  // with pid
  // point_msg.data = width / 1.5;
  // state_msg.data = cx;

  // pid_set_point_pub_.publish(point_msg);
  // pid_state_pub_.publish(state_msg);

  // twist_msg_.linear.x = 0.2;
  // twist_msg_.angular.z = effort_value_ / 200;

  cmd_vel_pub_.publish(twist_msg_);
}

void RobocopRacetrack::stopMoving()
{
  twist_msg_.linear.x = 0;
  twist_msg_.angular.z = 0;
  cmd_vel_pub_.publish(twist_msg_);
}

void RobocopRacetrack::effortCallback(const std_msgs::Float64::ConstPtr &effort_msg)
{
  effort_value_ = effort_msg->data;
}