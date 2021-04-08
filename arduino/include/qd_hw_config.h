#ifndef QdHwConfig_h
#define QdHwConfig_h

#include "qd_hw_control.h"

#define PI 3.1415926535897932384626433832795

//Global variables
const char cmd_topic[] = "hw_cmd";
const char feedback_topic[] = "hw_feedback";
const char imu_topic[] = "imu_feedback";
const int pulsemin = 555;
const int servo_freq = 60;
const int loop_hz = 20;

float initPositions[12] = {0,-90,0,
                           0,90,0,
                           0,-90,0,
                           0,90,0};

float compensationArrayMec[12] = { 0.0,  0.0,  0.0,
                                   0.0,  0.0,  0.0,
                                   0.0,  0.0,  0.0,
                                   0.0,  0.0,  0.0};                      

//Pour M4 c'est 90 deg pcq son range est de 90
float compensationArrayROS[12] = { 135.0,  225.0,  135.0,
                                   90.0,   45.0,  135.0,
                                   135.0,  225.0,  135.0,
                                   135.0,   45.0,  135.0};
                                   
int jointLimit[12][2] = { {-30, 45}, {-110, 125}, {-75, 135},
                          {-45, 30}, {-125, 110}, {-135, 75},
                          {-30, 45}, {-110, 125}, {-75, 135},
                          {-45, 30}, {-125, 110}, {-135, 75} };

int jointLimitPulse[12][2];

int analog_pins[12] = {0, 1, 2,
                       3, 4, 5,
                       6, 7, 8,
                       9, 10, 11};

// Le M4 est celui de 180 deg et M4 et M5 on été échan
const int pulsemax[12] = {2395, 2400, 2410,
                          2350, 2410, 2425,
                          2417, 2405, 2415,
                          2415, 2410, 2425};

#endif