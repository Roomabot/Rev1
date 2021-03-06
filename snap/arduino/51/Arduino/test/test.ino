#include <PID_v1.h>

#define SPEED  70 //0-255

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

double Setpoint, InputRight, OutputRight, InputLeft, OutputLeft;
PID myPIDRight(&InputRight, &OutputRight, &Setpoint, 100, 20, 0.01, DIRECT);
PID myPIDLeft(&InputLeft, &OutputLeft, &Setpoint, 100, 20, 0.01, DIRECT);

long rightEncoderTick = 0;
long leftEncoderTick = 0;

const float wheelDiameter = 0.065;
const float wheelBase = 0.1475;
const float encoderRevolution = 4172; // number of ticks for 1 revolution

float x = 0.0;
float y = 0.0;
float theta = 0.0;

unsigned long lastPoseUpdate; 

void driveBackward(){
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
}

void driveForward(){
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
}

void rotateCW(){
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
}

void rotateCCW(){
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
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
      //Serial.println("1");
    }
    else {
      rightEncoderTick--; //CCW
      //Serial.println("2");
    }
  }
  else{
    if (digitalRead(rightMotorEncoderB) == LOW){
      rightEncoderTick++;  //CW
      //Serial.println("3");
    }
    else {
      rightEncoderTick--; //CCW
     // Serial.println("4");
    }
  }
}

void rightEncoderBUpdate(){
  if (digitalRead(rightMotorEncoderA) == HIGH){
    if (digitalRead(rightMotorEncoderB) == HIGH){
      rightEncoderTick--;  //CCW
      //Serial.println("5");
    }
    else {
      rightEncoderTick++; //CW
      //Serial.println("6");
    }
  }
  else{
    if (digitalRead(rightMotorEncoderB) == LOW){
      rightEncoderTick--;  //CCW
      //Serial.println("7");
    }
    else {
      rightEncoderTick++; //CW
      //Serial.println("8");
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

void updatePose(){
  float distanceRight, distanceLeft, distanceCenter, rightRPM, leftRPM;

  float delta = millis()-lastPoseUpdate;
  
  InputRight = ((abs(rightEncoderTick)/encoderRevolution)/delta)*1000;
  InputLeft = ((abs(leftEncoderTick)/encoderRevolution)/delta)*1000;
  myPIDRight.Compute();
  myPIDLeft.Compute();
  /*if(OutputRight<30 || OutputLeft<30){
    analogWrite(rightMotorPWM, 0); //ENA pin
    analogWrite(leftMotorPWM, 0); //ENA pin
  }
  else{
    analogWrite(rightMotorPWM, OutputRight); //ENA pin
    analogWrite(leftMotorPWM, OutputLeft); //ENA pin
  }*/
  analogWrite(rightMotorPWM, OutputRight); //ENA pin
    analogWrite(leftMotorPWM, OutputLeft); //ENA pin
  

  Serial.print(InputRight);
  Serial.print("  ");
  Serial.print(InputLeft);
  Serial.print("  ");
  Serial.print(OutputRight);
  Serial.print("  ");
  Serial.print(OutputLeft);
  Serial.println("");
  
  
  
  distanceRight = (PI*wheelDiameter)*(rightEncoderTick/encoderRevolution);
  distanceLeft = (PI*wheelDiameter)*(leftEncoderTick/encoderRevolution);
  rightEncoderTick=0;
  leftEncoderTick=0;
  
  distanceCenter = (distanceLeft+distanceRight)/2.0;
  
  theta = theta + (distanceRight-distanceLeft)/wheelBase;
  //normalizing angle between [PI,-PI]
  if(theta>PI){
	theta = theta-2.*PI;
  }
  if(theta<-PI){
	theta = theta+2.*PI;
  }

  x = x + distanceCenter*cos(theta);
  y = y + distanceCenter*sin(theta);
}

void printData(){
  Serial.print("Right Ticks = ");
  Serial.print(rightEncoderTick);
  Serial.print("    Left Ticks = ");
  Serial.print(leftEncoderTick);
  Serial.print("    x = ");
  Serial.print(x);
  Serial.print("    y = ");
  Serial.print(y);
  Serial.print("    theta = ");
  Serial.println(theta);
}

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
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

  Setpoint = 0;
  myPIDRight.SetOutputLimits(0, 255);
  myPIDRight.SetMode(AUTOMATIC);
  myPIDLeft.SetOutputLimits(0, 255);
  myPIDLeft.SetMode(AUTOMATIC);
  
  //Controlling speed (0 = off and 255 = max speed):
  analogWrite(rightMotorPWM, 0); //ENA pin
  analogWrite(leftMotorPWM, 0); //ENA pin
  
  lastPoseUpdate = millis();
 
}

void loop() {
  Setpoint=0.8;
  //stopRobot();
  rotateCW();
  //driveForward();
  while(1){
    
    //printData();
    if((millis()-lastPoseUpdate)>=100){//update position estimate every 250ms
      updatePose(); //commented out intially so I can make sure the encoder counts look right
      lastPoseUpdate=millis();
    }
    if(Serial.available()){
      Setpoint=0;
      stopRobot();
      
    }
  }
}
