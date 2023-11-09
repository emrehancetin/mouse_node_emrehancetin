#include "ros/ros.h"
#include "std_msgs/UInt8MultiArray.h"
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    const char *mousePath = "/dev/input/mouse0";


    ros::init(argc, argv, "mouse_publisher");
    ros::NodeHandle nh;

   
    ros::Publisher mouse_pub = nh.advertise<std_msgs::UInt8MultiArray>("/mouse_node", 1000);
    std_msgs::UInt8MultiArray mouse_msg;

    int fd = open(mousePath, O_RDONLY);
    if (fd == -1) {
        ROS_ERROR("ERROR Opening %s\n", mousePath);
        return 1;
    }

    char data [3];
    while (ros::ok()) {
        if(read(fd, data, sizeof(data)) > 0) {

            mouse_msg.data.clear();

            for (int i = 0; i < 3; ++i) {
                mouse_msg.data.push_back(data[i]);
            }

            mouse_pub.publish(mouse_msg);
            ros::spinOnce();
        }
    }
    close(fd);
    return 0;
}