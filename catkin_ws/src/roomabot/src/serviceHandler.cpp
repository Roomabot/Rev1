#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "ros/ros.h"
#include "ros/package.h"
#include "roomabot/serviceCommand.h"
#include "std_msgs/String.h"

#define LOOPRATE 10
#define TIMEBETWEENSTATUS 2.0

#define CONNECTIONSTATUS "Connection Status"
#define START "Start"
#define SAVE "Save"
#define LOAD "Load"

void updateConnectionStatus(ros::Publisher *pub){
	bool dataProcessStatus=false;
	bool arduinoStatus=false;
	
	roomabot::serviceCommand msg;
	msg.command=CONNECTIONSTATUS;
	std::string path = ros::package::getPath("roomabot") + "/tmp/tmpStatus.txt";

	//checking all active nodes to see if dataProcessing and arduino nodes are up
	system(("rosnode list > " + path +" 2>/dev/null").c_str());
	std::ifstream file(path);
	
	if(file.is_open()){
		std::string line;
		while(getline(file,line)){
			if(line.compare("/dataProcessor")==0){
				dataProcessStatus=true;
			}
			else if(line.compare("/serial_node")==0){
				arduinoStatus=true;
			}		
		}
	}
	
	if(dataProcessStatus==true && arduinoStatus==true){
		msg.arg1="1";
	}
	else{
		msg.arg1="0";
	} 
	
	pub->publish(msg);
}

void serviceRequest(const roomabot::serviceCommand::ConstPtr& msg){
	
	std::string path = ros::package::getPath("roomabot") + "/tmp/tmpServiceRequest.txt";

	if(msg->command.compare(START)==0){
		printf("Recieved Start command\n");
		//closing gmapping, map_server, arduino and dataProcessing nodes
		//starting arduino, dataProcessing and gmapping node again to reset
		system(("rosnode list >"+ path+ " 2>/dev/null").c_str());
		std::ifstream file(path);
		
		if(file.is_open()){
			std::string line;
			while(getline(file,line)){
				if(line.compare("/dataProcessor")==0){
					system(("rosnode kill " + line + " >/dev/null 2>/dev/null").c_str());
					printf("stopped dataprocessor\n");
				}
				else if(line.compare("/serial_node")==0){
					system(("rosnode kill " + line + " >/dev/null 2>/dev/null").c_str());
					printf("stopped arduino\n");
				}		
				else if(line.compare("/slam_gmapping")==0){
					system(("rosnode kill " + line + " >/dev/null 2>/dev/null").c_str());
					printf("stopped gmapping\n");
				}
				else if(line.find("/map_server")==0){//if it starts with map_server*
					system(("rosnode kill " + line + " >/dev/null 2>/dev/null").c_str());
					printf("stopped map_sever\n");
				}
				
			}
		}
		std::string tmpLaunch = ros::package::getPath("roomabot") + "/tmp/tmpLaunch.txt";	
		system(("roslaunch roomabot roomabot_start.launch >"+tmpLaunch+" 2>&1 &").c_str());
		printf("starting nodes again\n");
		
		
	}
	else if(msg->command.compare(SAVE)==0){
	
	}
}

int main(int argc, char **argv){
	
	ros::init(argc, argv, "serviceHandler");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe<roomabot::serviceCommand>("/service_request",10, serviceRequest);
	ros::Publisher pub = nh.advertise<roomabot::serviceCommand>("/status", 1);
	ros::Rate loop_rate(LOOPRATE);
	
	double now,last;
	
	last=ros::Time::now().toSec();
	
	while(ros::ok()){
		now=ros::Time::now().toSec();
		if(now-last>TIMEBETWEENSTATUS){
			updateConnectionStatus(&pub);
			last=ros::Time::now().toSec();
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
	
	return 0;
	
}
