#include "MotorController.h"

void setup() {
  servoInit();
  computeLimits();
  moveMotor(initPositions);
  rosInit();
}

void loop() {
  readAngles(feedback_msg);
  feedback_pub.publish(&feedback_msg);
  nh.spinOnce();
  delay(1.00/LOOP_HZ);
}
