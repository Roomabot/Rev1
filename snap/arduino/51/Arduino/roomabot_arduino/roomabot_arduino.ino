#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32MultiArray.h>
#include <PID_v1.h>

//constants
#define MAXTIMEBETWEENINSTRUCTION 200
#define MAXTIMEBETWEENTRANSFORM 10 

#define rightMotorPin1 7
#define rightMotorPin2 8
#define rightMotorPWM 9

#define leftMotorPin1 4
#define leftMotorPin2 5
#define leftMotorPWM 6

#define rightMotorEncoderA 18
#define rightMotorEncoderB 19

#define leftMotorEncoderA 2
#define leftMotorEncoderB 3

#define LOWESTSPEED 160
#define HIGHESTSPEED 100

//global variables
double SetpointRight, SetpointLeft, InputRight, OutputRight, InputLeft, OutputLeft;

PID myPIDRight(&InputRight, &OutputRight, &SetpointRight, 80, 26, 3, DIRECT);
PID myPIDLeft(&InputLeft, &OutputLeft, &SetpointLeft, 80, 26, 3, DIRECT);

unsigned long lastTransformUpdate=0;

double rightEncoderTick = 0;
double leftEncoderTick = 0;

const float wheelDiameter = 0.065;
const float wheelBase = 0.149;
const float encoderRevolution = 4172; // number of ticks for 1 revolution

float x = 0.0;
float y = 0.0;
float theta = 0.0; 
int driveState=0;

std_msgs::Float32MultiArray pose_estimate;

void driveBackward(){
  driveState=1;
  SetpointRight = 0.65;
  SetpointLeft = 0.65;
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
}

void driveForward(){
  driveState=1;    
  SetpointRight = 0.65;
  SetpointLeft = 0.65;
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
} 

void rotateCW(){
  driveState=0;
  SetpointRight = 0.7;
  SetpointLeft = 0.7;
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
}

void rotateCCW(){
  driveState=0;
  SetpointRight = 0.7;
  SetpointLeft = 0.7;
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
}

void stopRobot(){
  driveState=0;
  SetpointRight = 0.0;
  SetpointLeft = 0.0;
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
  
  //PID update
  float delta = millis()-lastTransformUpdate; 
  
  InputRight = ((abs(rightEncoderTick)/encoderRevolution)/delta)*1000;
  InputLeft = ((abs(leftEncoderTick)/encoderRevolution)/delta)*1000;
  myPIDRight.Compute();
  myPIDLeft.Compute();
  
  analogWrite(rightMotorPWM, OutputRight); //ENA pin
  analogWrite(leftMotorPWM, OutputLeft); //ENA pin
  
  pose_estimate.data[3]=InputRight;
  pose_estimate.data[4]=InputLeft;
  pose_estimate.data[5]=OutputRight;
  pose_estimate.data[6]=OutputLeft;
  
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
  
  SetpointRight = 0;
  SetpointLeft = 0;
  myPIDRight.SetOutputLimits(30, 255);
  myPIDRight.SetMode(AUTOMATIC);
  myPIDLeft.SetOutputLimits(30, 255);
  myPIDLeft.SetMode(AUTOMATIC);
  
  //Controlling speed (0 = off and 255 = max speed):
  analogWrite(rightMotorPWM, 0); //ENA pin
  analogWrite(leftMotorPWM, 0); //ENB pin

  
  
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);

  pose_estimate.data = (float*)malloc(sizeof(float)*7);
  pose_estimate.data_length = 7;
  pose_estimate.data[0] = x;
  pose_estimate.data[1] = y;
  pose_estimate.data[2] = theta;
  pose_estimate.data[3] = 0; 
  pose_estimate.data[4] = 0; 
  pose_estimate.data[5] = 0; 
  pose_estimate.data[6] = 0;   
  pub.publish(&pose_estimate);
  lastTransformUpdate=millis();
  
}

void loop()
{ 
  if((millis()-lastTransformUpdate)>MAXTIMEBETWEENTRANSFORM){//Send transform periodically
	  updateTransform();
  }
  
  nh.spinOnce();
}
