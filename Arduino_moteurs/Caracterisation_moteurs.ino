#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

// Un jeu de 65 a ete laisse a chaque cote
// Pulse de 555 represente 0 degree
// Pulse de 2385 represente 270 degrees

#define PULSEMIN_M0 555 // Ne pas aller en dessous de 490, limite inferieure
#define PULSEMAX_M0 2395 // Ne pas aller au dessus de 2450, limite supérieure

#define PULSEMIN_M1 555
#define PULSEMAX_M1 2395

#define PULSEMIN_M2 555
#define PULSEMAX_M2 2395

#define PULSEMIN_M3 555
#define PULSEMAX_M3 2395




#define SERVO_FREQ 60


void setup() {
  Serial.begin(9600);
  Serial.println("Caracterisation des moteurs");

  driver.begin();
  driver.setOscillatorFrequency(27000000);
  driver.setPWMFreq(SERVO_FREQ);

  yield();
}


int angleToPulse(int ang, int moteur) {

  int pulse = 0;
  
  switch(moteur){
    case 0: pulse = map(ang, 0, 270, PULSEMIN_M0, PULSEMAX_M0);
    case 1: pulse = map(ang, 0, 270, PULSEMIN_M1, PULSEMAX_M1);
    case 2: pulse = map(ang, 0, 270, PULSEMIN_M2, PULSEMAX_M2);
    case 3: pulse = map(ang, 0, 270, PULSEMIN_M3, PULSEMAX_M3);
  }

  return pulse;
}


void loop() {
  //driver.writeMicroseconds(0, 2350);
  

  driver.writeMicroseconds(0, PULSEMIN_M0);
  delay(3000);
  driver.writeMicroseconds(0,angleToPulse(180,0));
  delay(3000);
  
  driver.writeMicroseconds(1, PULSEMIN_M1);
  delay(3000);
  driver.writeMicroseconds(1,angleToPulse(180,1));
  delay(3000);

  driver.writeMicroseconds(2, PULSEMIN_M2);
  delay(3000);
  driver.writeMicroseconds(2,angleToPulse(180,2));
  delay(3000);

  driver.writeMicroseconds(3, PULSEMIN_M3);
  delay(3000);
  driver.writeMicroseconds(3,angleToPulse(180,3));
  delay(3000);

}
