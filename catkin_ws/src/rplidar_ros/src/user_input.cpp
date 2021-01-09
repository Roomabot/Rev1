#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <termios.h>

#define LOOPRATE 50

int main(int argc, char **argv){
	
	ros::init(argc, argv, "user_input");
	
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<std_msgs::String>("/user_input", 1);
	ros::Rate loop_rate(LOOPRATE);
	
	
	struct termios old_tio, new_tio;
	char input;
	/* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO,&old_tio);
    /* we want to keep the old setting to restore them a the end */
    new_tio=old_tio;
    /* disable canonical mode (buffered i/o) and local echo */
    new_tio.c_lflag &=(~ICANON & ~ECHO);
    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
	
	while (ros::ok())
	{		
		std_msgs::String msg;
		std::stringstream ss;
		input=getchar();
		fflush(stdin);
		if(input==119){//if w is pressed
			ss << "w";
			msg.data = ss.str();
			ROS_INFO("w was pressed: %s", msg.data.c_str());
			pub.publish(msg);
		}
		else if(input==115){//if s is pressed
			ss << "s";
			msg.data = ss.str();
			ROS_INFO("s was pressed: %s", msg.data.c_str());
			pub.publish(msg);
		}
		else if(input==100){//if d is pressed
			ss << "d";
			msg.data = ss.str();
			ROS_INFO("d was pressed: %s", msg.data.c_str());
			pub.publish(msg);
		}
		else if(input==97){//if a is pressed
			ss << "a";
			msg.data = ss.str();
			ROS_INFO("a was pressed: %s", msg.data.c_str());
			pub.publish(msg);
		}
		else{
			printf("Invalid Input");
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
	
    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
	return 0;
}