#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32MultiArray.h>

//constants
#define MAXTIMEBETWEENINSTRUCTION 200
#define MAXTIMEBETWEENTRANSFORM 250


//global variables
unsigned long lastControlInput=0;
unsigned long lastTransformUpdate=0;
float distance=0.0;
float theta=0.0;
std_msgs::Float32MultiArray pose_estimate;
float currentPose[3]={0.0,0.0,0.0};



void controlCallback(const std_msgs::String& msg){
  if(strcmp(msg.data,"w")==0){//if arduino recieves instruction to move forward
    //driveForward();
    distance += 0.1;
    digitalWrite(LED_BUILTIN, HIGH);
    lastControlInput=millis();
  }
  else if(strcmp(msg.data,"s")==0){//if arduino recieves instruction to move backwards
    //driveBackward();
    distance -= 0.1;
    digitalWrite(LED_BUILTIN, HIGH);
    lastControlInput=millis();
  }
  else if(strcmp(msg.data,"a")==0){//if arduino recieves instruction to move ccw
    //driveCCW();
    theta += 0.0873;
    digitalWrite(LED_BUILTIN, HIGH);
    lastControlInput=millis();
  }
  else if(strcmp(msg.data,"d")==0){//if arduino recieves instruction to move cw
    //driveCW();
    theta -= 0.0873;
    digitalWrite(LED_BUILTIN, HIGH);
    lastControlInput=millis();
  }
}

ros::NodeHandle  nh; 
ros::Subscriber<std_msgs::String> sub("/user_input", &controlCallback );
ros::Publisher pub("/pose_estimate", &pose_estimate);


void updateTransform(){
  currentPose[0] += distance*cos(theta);//x
  currentPose[1] += distance*sin(theta);//y
  currentPose[2] = theta;

  pose_estimate.data = currentPose;
  pub.publish(&pose_estimate);
  lastTransformUpdate=millis();
  distance=0.0;
}



void setup()
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);

  pose_estimate.data = (float*)malloc(sizeof(float)*3);
  pose_estimate.data_length = 3;
  pose_estimate.data[0] = currentPose[0];
  pose_estimate.data[1] = currentPose[1];
  pose_estimate.data[2] = currentPose[2];  
  pub.publish(&pose_estimate);
  lastTransformUpdate=millis();

  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{

  if((millis()-lastControlInput)>MAXTIMEBETWEENINSTRUCTION){//if no drive instruction was recieved in the last 200ms,then stop the motors
    //stop();
    digitalWrite(LED_BUILTIN, LOW);
    lastControlInput=millis();  
  }
  
  if((millis()-lastTransformUpdate)>MAXTIMEBETWEENTRANSFORM){//Send transform periodically
	  updateTransform();
    //digitalWrite(LED_BUILTIN, HIGH);
  }
  
  nh.spinOnce();
  delay(1);
}
