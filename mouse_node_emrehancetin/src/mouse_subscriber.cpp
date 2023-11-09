#include "ros/ros.h"
#include "std_msgs/UInt8MultiArray.h"

void sendLog(const std_msgs::UInt8MultiArray::ConstPtr& msg){
    ROS_INFO_STREAM("Mouse data received: ");
    for (int i = 0; i < msg->data.size(); ++i) {
        ROS_INFO_STREAM((int)msg->data[i] << " ");
    }
    ROS_INFO("");

}

int main(int argc, char **argv){
    ros::init(argc, argv, "mouse_subscriber");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/mouse_node", 1000, sendLog);

    ros::spin();

    return 0;
}