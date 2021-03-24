#include "MotorController.h"

void setup() {
  driver.begin();
  driver.setOscillatorFrequency(27000000);
  driver.setPWMFreq(SERVO_FREQ);
  computeLimits();
  moveMotor(initPositions);

  node_handle.getHardware()->setBaud(115200);
  node_handle.initNode();
  ros::Subscriber<std_msgs::Float64MultiArray> motor_subscriber("hw_cmd", &subscriberCallback);
  node_handle.subscribe(motor_subscriber);
}

void loop() {
  node_handle.spinOnce();
  delay(10);
}
