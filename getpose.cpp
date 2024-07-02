#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "dobot/SetCmdTimeout.h"
#include <unistd.h>
#include "dobot/GetPose.h"
int main(int argc, char **argv)
{
    ros::init(argc, argv, "DobotClient");
    ros::NodeHandle n;
    ros::ServiceClient client;
    // SetCmdTimeout
    client = n.serviceClient<dobot::SetCmdTimeout>("/DobotServer/SetCmdTimeout");
    dobot::SetCmdTimeout srv1;
    srv1.request.timeout = 3000;
    if (client.call(srv1) == false) {
        ROS_ERROR("Failed to call SetCmdTimeout. Maybe DobotServer isn't started yet!");
        return -1;
    }
    // Getting
    do{  
        client = n.serviceClient<dobot::GetPose>("/DobotServer/GetPose");
        dobot::GetPose num1;
        client.call(num1); 
	ROS_INFO("x:%f",float(num1.response.x));
	ROS_INFO("y:%f",float(num1.response.y));
	ROS_INFO("z:%f",float(num1.response.z));
    } while(0);
    
    return 0;
}
