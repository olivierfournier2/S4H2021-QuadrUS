/*
Projet S3 GRO 2020
Class to communicate to MPU6050 IMU
@authors Marc Rousseau, Simon Chamorro
@version 1.0 25/04/2020
source : https://github.com/TKJElectronics/Example-Sketch-for-IMU-including-Kalman-filter
*/


#include "Arduino.h"
#include <Wire.h>
#include "Kalman.h" // Source: https://github.com/TKJElectronics/KalmanFilter


#ifndef Capteur_MPU6050_h
#define Capteur_MPU6050_h

#define BUZZER 12 


class Capteur_MPU6050
{
  public:
    void init();
	int UpdateAttitude();		
    void Acc_getValues(double *accX,double *accY,double *accZ);
	void Gyro_getValues(double *gyroX,double *gyroY,double *gyroZ);
	void Temp_getValue(double *temperature);
	void Sensor_getValues(double *accX,double *accY,double *accZ, double *temperature, double *gyroX,double *gyroY,double *gyroZ);
	void updateValues();
	void getAngles(double *angX, double *angY, int option);
    uint8_t i2cWrite(uint8_t registerAddress, uint8_t *data, uint8_t length, bool sendStop);
	uint8_t i2cWrite(uint8_t registerAddress, uint8_t data, bool sendStop);
	uint8_t i2cRead(uint8_t registerAddress, uint8_t *data, uint8_t nbytes);

};

#endif // 