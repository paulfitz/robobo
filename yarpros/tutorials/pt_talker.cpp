#include <ros/ros.h>
#include <sstream>

#include "Point.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pt_talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<tutorial::Point>("pt_chatter", 100);
  ros::Rate loop_rate(1);
  int count = 0;
  while (ros::ok())
  {
    tutorial::Point msg;
    msg.x = 1;
    msg.y = 2;
    msg.z = 3;
    chatter_pub.publish(msg);
    ROS_INFO("I published a point");
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
}
