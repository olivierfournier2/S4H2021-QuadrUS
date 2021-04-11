/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();;

int pos = 0;    // variable to store the servo position
const int pulsemin = 555;
const int pulsemax[12] = {2395, 2400, 2410,
                          2350, 2410, 2425,
                          2417, 2405, 2415,
                          2415, 2410, 2425};

int degToPulse(float ang, int motorIndex) {
  if (motorIndex == 3)
  {
    return ang*(pulsemax[motorIndex]-pulsemin)/180.0 + pulsemin;
  } else {
    return ang*(pulsemax[motorIndex]-pulsemin)/270.0 + pulsemin;
  }
}

void setup() {
  driver.begin();
  driver.setOscillatorFrequency(27000000);
  driver.setPWMFreq(60);
}

void loop() {

  driver.writeMicroseconds(0,degToPulse(135,0));
  //delay(1000);
}
