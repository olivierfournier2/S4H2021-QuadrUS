#ifndef QdHwControl_h
#define QdHwControl_h

#include <Adafruit_PWMServoDriver.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Float64MultiArray.h>
#include <string.h>

void computeLimits();
int degToPulse(float ang);
float radToDeg(float angleRad);
float degToRad(float angleDeg);
void subscriberCallback(const std_msgs::Float64MultiArray& cmd_msg);
void moveMotor(float cmdAngle[12]);
float compensateCommand(float rawAngle, int index);
void motorController(int pulseCommand[12]);
float analogToAngle(int analog_value);
void rosInit();
void servoInit();
void readAngles(std_msgs::Float64MultiArray feedback_data);

//Config variables declaration
extern const char cmd_topic[];
extern const char feedback_topic[];
extern const int loop_hz;
extern const int pulsemin;
extern const int pulsemax;
extern const int servo_freq;
extern float initPositions[12];
extern float compensationArrayMec[12] ;
extern float compensationArrayROS[12];
extern int jointLimit[12][2];
extern int analog_pins[12];

//ROS config declarations
extern ros::NodeHandle nh;
extern std_msgs::Float64MultiArray cmd_msg;
extern std_msgs::Float64MultiArray feedback_msg;
extern ros::Publisher feedback_pub;
extern ros::Subscriber<std_msgs::Float64MultiArray> cmd_sub;

//Servo config declarations
extern Adafruit_PWMServoDriver driver;

#endif
