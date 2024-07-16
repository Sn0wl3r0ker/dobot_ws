#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "dobot/SetCmdTimeout.h"
#include <unistd.h>

#include "dobot/SetPTPCmd.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "DobotClient");
    ros::NodeHandle n;
    ros::ServiceClient client;
    client = n.serviceClient<dobot::SetCmdTimeout>("/DobotServer/SetCmdTimeout");
    dobot::SetCmdTimeout srv1;
    srv1.request.timeout = 3000;
    if (client.call(srv1) == false) {
        ROS_ERROR("Failed to call SetCmdTimeout. Maybe DobotServer isn't started yet!");
        return -1;
    }
        client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
        dobot::SetPTPCmd srv;
        do{
            srv.request.ptpMode = 1;
            srv.request.x = 250;
            srv.request.y = 75;
            srv.request.z = 0;
            srv.request.r = 0;
	    ROS_INFO("1 point");
            client.call(srv);
        }while(0);
    return 0;
}
