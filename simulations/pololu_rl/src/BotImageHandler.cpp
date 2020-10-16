#include <pololu_rl/BotImageHandler.hpp>

BotImageHandler::BotImageHandler(ros::NodeHandle &nh) : nh_(nh), it_(nh)
{
    init();
}

BotImageHandler::~BotImageHandler() {}

void BotImageHandler::init()
{
    image_raw_sub_ = it_.subscribe("/camera/image_raw", 1, &BotImageHandler::imageCallback, this);
    image_cropped_pub_ = it_.advertise("/unity_image", 1);
    image_cropped_compressed_pub_ = it_.advertise("/unity_depth", 1);
}

void BotImageHandler::imageCallback(const sensor_msgs::Image::ConstPtr &image_msg)
{
    cv_bridge::CvImageConstPtr cvb_image;
    cv::Mat cv_image;
    sensor_msgs::ImagePtr img_msg;

    try
    {
        cvb_image = cv_bridge::toCvShare(image_msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (const cv_bridge::Exception &e)
    {
        ROS_ERROR("CV_Bridge exception: %s", e.what());
        return;
    }

    cv_image = cvb_image->image;
    // cv_image = cv_image(cv::Rect(0, 0, 640, 15));
    cv::resize(cv_image, cv_image, cv::Size(), 0.1563, 0.0104);

    img_msg = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::BGR8, cv_image).toImageMsg();

    image_cropped_pub_.publish(img_msg);
    image_cropped_compressed_pub_.publish(img_msg);
}