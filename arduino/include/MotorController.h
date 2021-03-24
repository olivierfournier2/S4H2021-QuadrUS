#ifndef MotorController_h
#define MotorController_h

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Float64MultiArray.h>


//Node config
ros::NodeHandle node_handle;
std_msgs::Float64MultiArray motor_msg;

//Function prototypes
Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();
int angleToPulse(float ang);
int radToPulse(float radAng);
void motorControl(int pulseCommand[12]); //Function that controls the motors with an internal loop
void speedSelection(int desiredSpeed);
void subscriberCallback(const std_msgs::Float64MultiArray& motor_msg); //Function called with each SpinOnce()
void motorController(int pulseCommand[12]); //Function that controls the motors without an internal loop

//Setup the topic the node is subscribed to
ros::Subscriber<std_msgs::Float64MultiArray> motor_subscriber("hw_cmd", &subscriberCallback);

//Global variables

int compensationPulse[12];

#define PI 3.1415926535897932384626433832795

#define PULSEMIN 555
#define PULSEMAX 2395

#define SERVO_FREQ 60

float compensationArrayMec[12] = { 0.0,  -1.0,  -7.0,
                                   7.5,   7.0,  -7.0,
                                  -5.0,   0.0,   0.0,
                                  -5.0,  -4.0,  -8.0};
                               

float compensationArrayROS[12] = { 135.0,  225.0,  135.0,
                                   135.0,   45.0,  135.0,
                                   135.0,   225.0,   135.0,
                                   135.0,  45.0,  135.0}; 

float compensationArray[12];
                                                          

//  MX: hanche/femur/tibia - left/right - front/rear    1475 pulses = 135 degrés
//Moteurs :             M0:H-L-F  M1:F-L-F  M2:T-L-F  M3:H-L-R  M4:F-L-R  M5:T-L-R  M6:H-R-F  M7:F-R-F  M8:T-R-F  M9:H-R-R  M10:F-R-R  M11:T-R-R
int currentPulse[12] = {1475,     1475,     1475,     1475,     1475,     1475,     1475,     1475,     1475,     1475,     1475,      1475};   // Position initiale en pulse

//Moteurs :                        M0                    M1                    M2         
int jointLimit[12][2] = { {angleToPulse(135 + compensationArrayMec[0] - 30), angleToPulse(135 + compensationArrayMec[0] + 45)}, {angleToPulse(135 + compensationArrayMec[1] - 110), angleToPulse(135 + compensationArrayMec[1] + 125)}, {angleToPulse(135 + compensationArrayMec[2] - 75), angleToPulse(135 + compensationArrayMec[2] + 135)},
                          {angleToPulse(135 + compensationArrayMec[3] - 45), angleToPulse(135 + compensationArrayMec[3] + 30)}, {angleToPulse(135 + compensationArrayMec[4] - 125), angleToPulse(135 + compensationArrayMec[4] + 110)}, {angleToPulse(135 + compensationArrayMec[5] - 135), angleToPulse(135 + compensationArrayMec[5] + 75)},
                          {angleToPulse(135 + compensationArrayMec[6] - 30), angleToPulse(135 + compensationArrayMec[6] + 45)}, {angleToPulse(135 + compensationArrayMec[7] - 110), angleToPulse(135 + compensationArrayMec[7] + 125)}, {angleToPulse(135 + compensationArrayMec[8] - 75), angleToPulse(135 + compensationArrayMec[8] + 135)},
                          {angleToPulse(135 + compensationArrayMec[9] - 45), angleToPulse(135 + compensationArrayMec[9] + 30)}, {angleToPulse(135 + compensationArrayMec[10] - 125), angleToPulse(135 + compensationArrayMec[10] + 110)}, {angleToPulse(135 + compensationArrayMec[11] - 135), angleToPulse(135 + compensationArrayMec[11] + 75)} };    // En pulse

int pulseInterval = 1;


//Transform degree angle to pulse
int angleToPulse(float ang) {
  int pulse = map(ang, 0, 270, PULSEMIN, PULSEMAX);
  return pulse;
}

//Transform rad angle to pulse
int radToPulse(float radAng) {
  int pulse = map(radAng*100,0 , (3 * PI / 2)*100, PULSEMIN, PULSEMAX);
  return pulse;
}

// Select the speed of the motors (1 : slowest / 5 : fastest)
// All motor will have the same speed
void speedSelection(int desiredSpeed) {
    switch (desiredSpeed) {
    case 1 : 
      pulseInterval = 1;
      break;
      
    case 2 : 
      pulseInterval = 5;
      break;

    case 3 : 
      pulseInterval = 10;
      break;

    case 4 : 
      pulseInterval = 15;
      break;

    case 5 : 
      pulseInterval = 20;
      break;
      
    
    }
  }


// Param pulseCommand must be an array of pulse not angle
// Use angleToPulse() function to populate array
void motorControl(int pulseCommand[12]) {
    bool stop = false;
    int lastStep = 0;

    for (int i = 0; i < 12; i++){
        if(pulseCommand[i] > jointLimit[i][1]){
            pulseCommand[i] = jointLimit[i][1];
          }
        else if(pulseCommand[i] < jointLimit[i][0]){
            pulseCommand[i] = jointLimit[i][0];
          }
      }
    
    while(stop == false) {
        stop = true;

        for (int i = 0; i < 12 ; i++){
          if (pulseCommand[i] > currentPulse[i]){
              lastStep = pulseCommand[i] - currentPulse[i];
              
              if ( lastStep < pulseInterval) {
                currentPulse[i] += lastStep;
              } 
              else {
                currentPulse[i] += pulseInterval;
              }
                
              driver.writeMicroseconds(i,currentPulse[i]);
            }
          else if (pulseCommand[i] < currentPulse[i]){
              lastStep = currentPulse[i] - pulseCommand[i];
              
              if ( lastStep < pulseInterval) {
                currentPulse[i] -= lastStep;
              } 
              else {
                currentPulse[i] -= pulseInterval;
              }
              
              driver.writeMicroseconds(i,currentPulse[i]);
            }
          else {
              delayMicroseconds(1000);
            }

          if (currentPulse[i] != pulseCommand[i]) {
              stop = false;
            }
        }
      } 
  }

void motorController(int pulseCommand[12]){

    for (int i = 0; i < 12; i++){
        if(pulseCommand[i] > jointLimit[i][1]){
            pulseCommand[i] = jointLimit[i][1];
          }
        else if(pulseCommand[i] < jointLimit[i][0]){
            pulseCommand[i] = jointLimit[i][0];
          }
      }
    
    for (int i=0; i < 12; i++){
        driver.writeMicroseconds(i, pulseCommand[i]);
    }
}


void subscriberCallback(const std_msgs::Float64MultiArray& motor_msg) {

  int command[12];
  float ros_motor_commands[12] = {motor_msg.data[0], motor_msg.data[1], motor_msg.data[2], motor_msg.data[3], motor_msg.data[4], 
  motor_msg.data[5], motor_msg.data[6], motor_msg.data[7], motor_msg.data[8], motor_msg.data[9], motor_msg.data[10], motor_msg.data[11]};
  
  float compensated_command[12];

  for(int i = 0; i < 12; i++){
    compensated_command[i] = compensationArray[i] + ros_motor_commands[i];
    command[i] = radToPulse(compensated_command[i]);
  };
  
  
  motorController(command);
}

#endif