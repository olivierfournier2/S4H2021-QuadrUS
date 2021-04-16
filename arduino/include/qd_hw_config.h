#ifndef QdHwConfig_h
#define QdHwConfig_h

#include "qd_hw_control.h"

#define PI 3.141592

//Global variables
const char cmd_topic[] = "hw_cmd";
const char feedback_topic[] = "hw_feedback";
const int pulsemin = 555;
const int servo_freq = 60;
const int loop_hz = 20;

float initPositions[12] = {0,0,0,
                           0,0,0,
                           0,0,0,
                           0,0,0};

float compensationArrayMec[12] = { 5.0,  -7.0,  -10.0,
                                   -2.0,  0.0,  5.0,
                                   7.0,  2.0,  -8.0,
                                   2.0,  -2.0,  12.0};                      

float compensationArrayROS[12] = { 135.0,  225.0,  135.0,
                                   90.0,   45.0,  135.0,
                                   135.0,  225.0,  135.0,
                                   135.0,   45.0,  135.0};
                                   
int jointLimit[12][2] = { {-23, 45}, {-90, 110}, {-80, 100},
                          {-45, 23}, {-110, 90}, {-100, 80},
                          {-23, 45}, {-90, 110}, {-80, 100},
                          {-45, 23}, {-110, 90}, {-100, 80} };

int jointLimitPulse[12][2];

int analog_pins[12] = {0, 1, 2,
                       3, 4, 5,
                       6, 7, 8,
                       9, 10, 11};

const int pulsemax[12] = {2395, 2400, 2410,
                          2350, 2410, 2425,
                          2417, 2405, 2415,
                          2415, 2410, 2425};

#endif