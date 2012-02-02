#include <ros/ros.h>
#include "Point.h"

void chatterCallback(const tutorial::PointConstPtr& msg)
{
  ROS_INFO("Received [%g,%g,%g]", msg->x, msg->y, msg->z);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pt_listener");
  ros::NodeHandle n;
  ros::Subscriber chatter_sub = n.subscribe("pt_chatter", 100, chatterCallback);
  ros::spin();
}

