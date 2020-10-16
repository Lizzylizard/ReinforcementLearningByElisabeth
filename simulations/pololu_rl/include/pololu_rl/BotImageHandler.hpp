#pragma once

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

class BotImageHandler
{
private:
    ros::NodeHandle &nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_raw_sub_;
    image_transport::Publisher image_cropped_pub_;
    image_transport::Publisher image_cropped_compressed_pub_;

    void init();
    void imageCallback(const sensor_msgs::Image::ConstPtr &image_msg);

public:
    BotImageHandler(ros::NodeHandle &nh);
    ~BotImageHandler();
};