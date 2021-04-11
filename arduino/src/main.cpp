#include "qd_hw_control.h"
#include "qd_hw_config.h"

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();
ros::NodeHandle nh;
std_msgs::Float64MultiArray cmd_msg;
std_msgs::Float64MultiArray feedback_msg;
//IMUdata imu_msg; //to test
ros::Publisher feedback_pub(feedback_topic, &feedback_msg);
//ros::Publisher imu_pub(imu_topic, &imu_msg);
ros::Subscriber<std_msgs::Float64MultiArray> cmd_sub(cmd_topic, &subscriberCallback);

void setup() {
  servoInit();
  computeLimits();
  moveMotor(initPositions);
  rosInit();
}

void loop() {
  readAngles(feedback_msg);
  feedback_pub.publish(&feedback_msg);
  //readIMU(imu_msg);
  //imu_pub.publish(&imu_msg);
  nh.spinOnce();
  delay(1000/loop_hz);
   // Mouvement de push up
  // Standing
  float positionsStanding[12] = {0,60,-10,
                         0,-60,10,
                         0,60,-10,
                         0,-60,10};
  for (int i = 0; i < 12; i++){
    positionsStanding[i] = initPositions[i] + positionsStanding[i];
  }
  moveMotor(positionsStanding);
  delay(5000);
  
  // Inter 1
  float positionsInter1[12] = {0,80,-35,
                         0,-80,35,
                         0,80,-35,
                         0,-80,35};
  for (int i = 0; i < 12; i++){
    positionsInter1[i] = initPositions[i] + positionsInter1[i];
  }
  moveMotor(positionsInter1);
  delay(1000);

  // Inter 2
  float positionsInter2[12] = {0,100,-60,
                         0,-100,60,
                         0,100,-60,
                         0,-100,60};
  for (int i = 0; i < 12; i++){
    positionsInter2[i] = initPositions[i] + positionsInter2[i];
  }
  moveMotor(positionsInter2);
  delay(1000);

  // Layed down
  float positionsLay[12] = {0,110,-80,
                         0,-110,80,
                         0,110,-80,
                         0,-110,80};
  for (int i = 0; i < 12; i++){
    positionsLay[i] = initPositions[i] + positionsLay[i];
  }
  moveMotor(positionsLay);
  delay(3000);

   // Inter 2
  moveMotor(positionsInter2);
  delay(1000);
  
  // Inter 1
  moveMotor(positionsInter1);
  delay(1000);

}
