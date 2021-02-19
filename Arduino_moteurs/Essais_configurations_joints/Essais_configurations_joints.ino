#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

#define PULSEMIN 555
#define PULSEMAX 2395

#define SERVO_FREQ 60

int actual_angle_0 = 135;
int actual_angle_1 = 135;
int actual_angle_2 = 135;

void setup() {
  Serial.begin(9600);
  Serial.println("Premier essai de configuration de joints");

  driver.begin();
  driver.setOscillatorFrequency(27000000);
  driver.setPWMFreq(SERVO_FREQ);

  driver.writeMicroseconds(0, angleToPulse(actual_angle_0));
  driver.writeMicroseconds(1, angleToPulse(actual_angle_1));
  driver.writeMicroseconds(2, angleToPulse(actual_angle_2));
  
  yield();
}


int angleToPulse(int ang) {
  int pulse = map(ang, 0, 270, PULSEMIN, PULSEMAX);
  return pulse;
}


void deplacement_fluide(int angle_actuel, int angle_voulu, int moteur) { 
  if (angle_voulu > angle_actuel){
    for (int i = angleToPulse(angle_actuel) ; i <= angleToPulse(angle_voulu) ; i++){
      driver.writeMicroseconds(moteur,i);
      if (i % 1 == 0){
        delay(1);
      }
    }
  }
  else if (angle_voulu < angle_actuel){
    for (int i = angleToPulse(angle_actuel); i >= angleToPulse(angle_voulu) ; i--){
      driver.writeMicroseconds(moteur,i);
      if (i % 1 == 0){
        delay(1);
      }
    }
  }
  return angle_voulu;
}


void loop() {
  
  Serial.println(driver.getPWM(1));
  actual_angle_1 = deplacement_fluide(actual_angle_1, 180, 1);
  
  actual_angle_2 = deplacement_fluide(angleToPulse(actual_angle_2), angleToPulse(90), 2);
  

  actual_angle_1 = deplacement_fluide(angleToPulse(actual_angle_1), angleToPulse(135), 1);
  
  actual_angle_2 = deplacement_fluide(angleToPulse(actual_angle_2), angleToPulse(135), 2);
  

  /*driver.writeMicroseconds(0,angleToPulse(135));
  driver.writeMicroseconds(2,angleToPulse(90));
  delay(50);
  driver.writeMicroseconds(1,angleToPulse(180));*/

}
