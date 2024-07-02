#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "dobot/SetCmdTimeout.h"
#include <unistd.h>
#include "dobot/SetHOMEParams.h"
#include "dobot/SetHOMECmd.h"

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
    
    // Setting
    do{  
        client = n.serviceClient<dobot::SetHOMEParams>("/DobotServer/SetHOMEParams");
        dobot::SetHOMEParams home;
        home.request.x = 200;
        home.request.y = 0;
        home.request.z = 25;
        home.request.r = 0;
        home.request.isQueued = 1;
	ROS_INFO("setting");
        client.call(home); 
    } while(0);
    
    // Running
    do{
        client = n.serviceClient<dobot::SetHOMECmd>("/DobotServer/SetHOMECmd");
        dobot::SetHOMECmd home2;
	ROS_INFO("homeing");
        client.call(home2);
    } while(0);

    return 0;
}
