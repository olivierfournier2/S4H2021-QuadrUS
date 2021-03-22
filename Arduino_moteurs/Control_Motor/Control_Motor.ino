#include "MotorController.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Premier essai de configuration de joints");

  driver.begin();
  driver.setOscillatorFrequency(27000000);
  driver.setPWMFreq(SERVO_FREQ);

  for(int i = 0; i < 12; i++){
      driver.writeMicroseconds(i, 1475);
    }

  node_handle.getHardware()->setBaud(115200);
  node_handle.initNode();
  node_handle.subscribe(motor_subscriber);

  for (int j = 0; j < 12; j++){
    compensationArray[j] = (compensationArrayMec[j]+compensationArrayROS[j]) * PI/180;
    compensationPulse[j] = radToPulse(compensationArray[j]);
  }

  speedSelection(2);
  yield();
}

void loop() {
  
  //Serial.println("Premier essai de configuration de joints");

  // Motors : AVANT : GAUCHE : Hanche, Femur, Tibia; DROIT : Hanche, Femur, Tibia, ARRIERE : GAUCHE : Hanche, Femur, Tibia; DROIT : Hanche, Femur, Tibia, 
  // Motor #:                     1       2     3               4       5     6                           7     8       9               10    11      12

  // Mouvement de push up
  
  speedSelection(2);

  float positionInit[12] = {135,180,135,135,90,135,135,180,135,135,90,135};
  int pulseInit[12];
  
  for (int i = 0; i < 12; i++){
    pulseInit[i] =  angleToPulse(positionInit[i] + compensationArrayMec[i]);
  }

  motorControl(pulseInit);

  delay(2000);

  float frontDown[12] = {135,225,90,135,45,180,135,225,90,135,45,180};
  int pulseFrontDown[12];
  
  for (int i = 0; i < 12; i++){
    pulseFrontDown[i] =  angleToPulse(frontDown[i] + compensationArrayMec[i]);
  }

  motorControl(pulseFrontDown);
  

  // S'assoir et se pencher vers l'avant
  /*
  speedSelection(2);

  float positionInit[12] = {135,180,135,135,90,135,135,180,135,135,90,135};
  int pulseInit[12];
  
  for (int i = 0; i < 12; i++){
    pulseInit[i] =  angleToPulse(positionInit[i] + compensationArrayMec[i]);
  }

  motorControl(pulseInit);

  delay(1000); // Is at init postion

  float frontDown[12] = {135,195,100,135,75,170,135,180,135,135,90,135};
  int pulseFrontDown[12];
  
  for (int i = 0; i < 12; i++){
    pulseFrontDown[i] =  angleToPulse(frontDown[i] + compensationArrayMec[i]);
  }

  motorControl(pulseFrontDown);

  delay(1000); // Is front incline
  

  float positionInit2[12] = {135,180,135,135,90,135,135,180,135,135,90,135};
  int pulseInit2[12];
  
  for (int i = 0; i < 12; i++){
    pulseInit[i] =  angleToPulse(positionInit[i] + compensationArrayMec[i]);
  }

  motorControl(pulseInit);

  delay(1000); // Is at init postion

  float rearDown[12] = {135,180,135,135,90,135,135,225,90,135,45,180};
  int pulserearDown[12];
  
  for (int i = 0; i < 12; i++){
    pulserearDown[i] =  angleToPulse(rearDown[i] + compensationArrayMec[i]);
  }

  motorControl(pulserearDown);

  delay(1000); // Is rear incline

  */
  
  
  
  //motorControl(compensationPulse);
  //node_handle.spinOnce();
  delay(1000);
}
