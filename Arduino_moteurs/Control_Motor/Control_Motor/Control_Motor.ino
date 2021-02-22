#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/UInt16MultiArray.h>

//Node config
ros::NodeHandle node_handle;
std_msgs::UInt16MultiArray motor_msg;

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();
int angleToPulse(int ang);
void motorControl(int pulseCommand[12]);
void speedSelection(int desiredSpeed);


#define PULSEMIN 555
#define PULSEMAX 2395

#define SERVO_FREQ 60

//  MX: hanche/femur/tibia - left/right - front/rear    1475 pulses = 135 degrés
//Moteurs :             M0:H-L-F  M1:F-L-F  M2:T-L-F  M3:H-L-R  M4:F-L-R  M5:T-L-R  M6:H-R-F  M7:F-R-F  M8:T-R-F  M9:H-R-R  M10:F-R-R  M11:T-R-R
int currentPulse[12] = {1475,     1475,     1475,     1475,     1475,     1475,     1475,     1475,     1475,     1475,     1475,      1475};   // Position initiale en pulse

//Moteurs :                        M0                    M1                    M2                   M3                   M4                     M5                    M6                  M7                     M8                  M9                     M10                  M11
int jointLimit[12][2] = { {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX} };    // En pulse

int pulseInterval = 1;


//Transform angle to pulse
int angleToPulse(int ang) {
  int pulse = map(ang, 0, 270, PULSEMIN, PULSEMAX);
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

void subscriberCallback(const std_msgs::UInt16MultiArray& motor_msg) {
  speedSelection(1);
  int ros_motor_commands[12] = {motor_msg.data[1], motor_msg.data[2], motor_msg.data[3], motor_msg.data[4], motor_msg.data[5], motor_msg.data[6], motor_msg.data[7], 1500, 1500, 1500, 1500, 1500};
  motorControl(ros_motor_commands);
}

ros::Subscriber<std_msgs::UInt16MultiArray> motor_subscriber("motor_command", &subscriberCallback);

void setup() {
  Serial.begin(9600);
  Serial.println("Premier essai de configuration de joints");

  driver.begin();
  driver.setOscillatorFrequency(27000000);
  driver.setPWMFreq(SERVO_FREQ);

  for(int i = 0; i < 12; i++){
      driver.writeMicroseconds(i, 1475);
    }

  node_handle.initNode();
  node_handle.subscribe(motor_subscriber);
  yield();
}

void loop() {
  
  /*speedSelection(1);

  int pulseCommand1 [12] = {700, 1300, 2200, 1000, 1800, 2000, 900, 2000, 2000, 2000, 2000, 2000};
  
  motorControl(pulseCommand1);

  speedSelection(1);

  int pulseCommand2 [12] = {2300, 1000, 1200, 700, 600, 1500, 2200, 1000, 1000, 1000, 1000, 1000};
  
  motorControl(pulseCommand2);*/

  //node_handle.spinOnce();
  //delay(100);

}
