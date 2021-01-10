#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32MultiArray.h>

//constants
#define MAXTIMEBETWEENINSTRUCTION 200
#define MAXTIMEBETWEENTRANSFORM 250

#define SPEED 100 //0-255

#define rightMotorPin1 4
#define rightMotorPin2 5
#define rightMotorPWM 6

#define leftMotorPin1 7
#define leftMotorPin2 8
#define leftMotorPWM 9

#define rightMotorEncoderA 2
#define rightMotorEncoderB 3

#define leftMotorEncoderA 18
#define leftMotorEncoderB 19


//global variables
unsigned long lastTransformUpdate=0;

long rightEncoderTick = 0;
long leftEncoderTick = 0;

const float wheelDiameter = 0.065;
const float wheelBase = 0.183;
const float encoderRevolution = 1800; // number of ticks for 1 revolution

float x = 0.0;
float y = 0.0;
float theta = 0.0; 

std_msgs::Float32MultiArray pose_estimate;

void driveForward(){
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
}

void driveBackward(){
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
}

void rotateCW(){
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
}

void rotateCCW(){
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
}

void stopRobot(){
  digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  
  digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
}

void rightEncoderAUpdate(){
  if (digitalRead(rightMotorEncoderA) == HIGH){
    if (digitalRead(rightMotorEncoderB) == HIGH){
      rightEncoderTick++;  //CW
    }
    else {
      rightEncoderTick--; //CCW
    }
  }
  else{
    if (digitalRead(rightMotorEncoderB) == LOW){
      rightEncoderTick++;  //CW
    }
    else {
      rightEncoderTick--; //CCW
    }
  }
}

void rightEncoderBUpdate(){
  if (digitalRead(rightMotorEncoderA) == HIGH){
    if (digitalRead(rightMotorEncoderB) == HIGH){
      rightEncoderTick--;  //CCW
    }
    else {
      rightEncoderTick++; //CW
    }
  }
  else{
    if (digitalRead(rightMotorEncoderB) == LOW){
      rightEncoderTick--;  //CCW
    }
    else {
      rightEncoderTick++; //CW
    }
  }
}

void leftEncoderAUpdate(){
  if (digitalRead(leftMotorEncoderA) == HIGH){
    if (digitalRead(leftMotorEncoderB) == HIGH){
      leftEncoderTick--;  //CW
    }
    else {
      leftEncoderTick++; //CCW
    }
  }
  else{
    if (digitalRead(leftMotorEncoderB) == LOW){
      leftEncoderTick--;  //CW
    }
    else {
      leftEncoderTick++; //CCW
    }
  }
}

void leftEncoderBUpdate(){
  if (digitalRead(leftMotorEncoderA) == HIGH){
    if (digitalRead(leftMotorEncoderB) == HIGH){
      leftEncoderTick++;  //CCW
    }
    else {
      leftEncoderTick--; //CW
    }
  }
  else{
    if (digitalRead(leftMotorEncoderB) == LOW){
      leftEncoderTick++;  //CCW
    }
    else {
      leftEncoderTick--; //CW
    }
  }
}

void controlCallback(const std_msgs::String& msg){
  if(strcmp(msg.data,"w")==0){//if arduino recieves instruction to move forward
    driveForward();
  }
  else if(strcmp(msg.data,"s")==0){//if arduino recieves instruction to move backwards
    driveBackward();
  }
  else if(strcmp(msg.data,"a")==0){//if arduino recieves instruction to move ccw
    rotateCCW();
  }
  else if(strcmp(msg.data,"d")==0){//if arduino recieves instruction to move cw
    rotateCW();
  }
  else if(strcmp(msg.data,"f")==0){//if arduino recieves instruction to stop
    stopRobot();
  }
}

ros::NodeHandle  nh; 
ros::Subscriber<std_msgs::String> sub("/user_input", &controlCallback );
ros::Publisher pub("/pose_estimate", &pose_estimate);


void updateTransform(){
  float distanceRight, distanceLeft, distanceCenter;
  
  distanceRight = (PI*wheelDiameter)*(rightEncoderTick/encoderRevolution);
  distanceLeft = (PI*wheelDiameter)*(leftEncoderTick/encoderRevolution);
  rightEncoderTick=0;
  leftEncoderTick=0;
  
  distanceCenter = (distanceLeft+distanceRight)/2.0;
  
  theta = theta + (distanceRight-distanceLeft)/wheelBase;
  //normalize angle between PI and -PI
  if(theta>PI){
    theta = theta-2.*PI;
  }
  if(theta<-PI){
    theta = theta+2.*PI;
  }
  x = x + distanceCenter*cos(theta);
  y = y + distanceCenter*sin(theta);

  pose_estimate.data[0] = x;
  pose_estimate.data[1] = y;
  pose_estimate.data[2] = theta;
  pub.publish(&pose_estimate);
  
  lastTransformUpdate=millis();
  
}



void setup()
{ 

  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(rightMotorEncoderA, INPUT_PULLUP);
  pinMode(rightMotorEncoderB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(rightMotorEncoderA), rightEncoderAUpdate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightMotorEncoderB), rightEncoderBUpdate, CHANGE);
  
  pinMode(leftMotorEncoderA, INPUT_PULLUP);
  pinMode(leftMotorEncoderB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(leftMotorEncoderA), leftEncoderAUpdate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(leftMotorEncoderB), leftEncoderBUpdate, CHANGE);
  
  pinMode(rightMotorPWM, OUTPUT); 
  pinMode(leftMotorPWM, OUTPUT); 
  
  //Controlling speed (0 = off and 255 = max speed):
  analogWrite(rightMotorPWM, SPEED); //ENA pin
  analogWrite(leftMotorPWM, SPEED); //ENA pin

  
  
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);

  pose_estimate.data = (float*)malloc(sizeof(float)*3);
  pose_estimate.data_length = 3;
  pose_estimate.data[0] = x;
  pose_estimate.data[1] = y;
  pose_estimate.data[2] = theta;  
  pub.publish(&pose_estimate);
  lastTransformUpdate=millis();
  
}

void loop()
{ 
  if((millis()-lastTransformUpdate)>MAXTIMEBETWEENTRANSFORM){//Send transform periodically
	  updateTransform();
  }
  
  nh.spinOnce();
  delay(1);
}
