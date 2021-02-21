#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

#define PULSEMIN 555
#define PULSEMAX 2395

#define SERVO_FREQ 60

//Moteurs :             M0    M1    M2    M3    M4    M5    M6    M7    M8    M9   M10  M11
int actualPulse[12] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};   // Position initiale en pulse

//Moteurs :                        M0                    M1                    M2                   M3                   M4                     M5                    M6                  M7                     M8                  M9                     M10                  M11
int jointLimit[12][2] = { {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX}, {PULSEMIN, PULSEMAX} };    // En pulse
int pulseInterval = 1;

void setup() {
  Serial.begin(9600);
  Serial.println("Premier essai de configuration de joints");

  driver.begin();
  driver.setOscillatorFrequency(27000000);
  driver.setPWMFreq(SERVO_FREQ);

  
  yield();
}


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
    //int pulseCounter = 1;
    
    while(stop == false) {
        stop = true;
        
        for (int i = 0; i < 12 ; i++){
          if (pulseCommand[i] > actualPulse[i] && actualPulse[i] < jointLimit[i][1]){
              actualPulse[i] += pulseInterval;
              driver.writeMicroseconds(i,actualPulse[i]);
            }

          if (pulseCommand[i] < actualPulse[i] && actualPulse[i] > jointLimit[i][0]){
              actualPulse[i] -= pulseInterval;
              driver.writeMicroseconds(i,actualPulse[i]);
            }


            if (actualPulse[i] < pulseCommand[i] && actualPulse[i] > jointLimit[i][0] && actualPulse[i] < jointLimit[i][1]) {
            stop = false;
          }
        }
      } 
  }


void loop() {
  speedSelection(2);

  //int pulseCommand1 [12] = {700, 2000, 1800, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000};
  int pulseCommand1 [12] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
  
  motorControl(pulseCommand1);

  speedSelection(3);

  int pulseCommand2 [12] = {2300, 1000, 1200, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
  
  //motorControl(pulseCommand2);

}
