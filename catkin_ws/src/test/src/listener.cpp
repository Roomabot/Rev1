#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <fstream>
#include <math.h>
#include <vector>
#include "/home/ubuntu/catkin_ws/src/test/include/test/GNUPlot.h"

#define RAD2DEG(x) ((x)*180./M_PI)

std::vector<std::string> script;
GNUPlot plotter;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
	std::ofstream myfile;
	myfile.open("/home/ubuntu/OUT");
    int count = scan->scan_time / scan->time_increment;
    ROS_INFO("I heard a laser scan %s[%d]:", scan->header.frame_id.c_str(), count);
    ROS_INFO("angle_range, %f, %f", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));

    for(int i = 0; i < count; i++) {
        float rad = scan->angle_min + scan->angle_increment * i;
		float degree = RAD2DEG(rad);
		float x = scan->ranges[i]*cos(rad);
		float y = scan->ranges[i]*sin(rad);
		myfile<<x<<"\t"<<y<<std::endl;
        ROS_INFO(": [%f, %f, %f, %f]", degree, scan->ranges[i],x,y);
    }
	plotter.execute(script);
	myfile.close();
}

int main(int argc, char **argv)
{
	script.push_back("set terminal x11");
	script.push_back("reset");
	script.push_back("set xrange [-7:7]");
	script.push_back("set yrange [-7:7]");
	script.push_back("plot '/home/ubuntu/OUT'");

	plotter.open();


    ros::init(argc, argv, "rplidar_node_client");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);

    ros::spin();

    return 0;
}

