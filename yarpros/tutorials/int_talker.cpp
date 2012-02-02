// example from ROS wiki

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <sstream>
int main(int argc, char** argv)
{
  ros::init(argc, argv, "int_talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int32>("int_chatter", 100);
  ros::Rate loop_rate(1);
  int count = 0;
  while (ros::ok())
  {
    std::stringstream ss;
    ss << "Hello there! This is message [" << count << "]";
    std_msgs::Int32 msg;
    msg.data = count;
    chatter_pub.publish(msg);
    ROS_INFO("I published the int in [%s]", ss.str().c_str());
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
}
