#include "qd_hw_control.h"

/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
void rosInit(){
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(cmd_sub);
  nh.advertise(feedback_pub);
  feedback_msg.data_length = 12;
  feedback_msg.data = (float *)malloc(sizeof(float) *12);
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
void servoInit(){
  driver.begin();
  driver.setOscillatorFrequency(27000000);
  driver.setPWMFreq(servo_freq);
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
void computeLimits() {
  for (int i = 0; i < 12; i++){
    for (int j = 0; j < 2; j++){
      jointLimit[i][j] =  degToPulse(135 + compensationArrayMec[i] + jointLimit[i][j]);
    }
  }
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
int degToPulse(float ang) {
  int pulse = map(ang, 0, 270, pulsemin, pulsemax);
  return pulse;
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
float radToDeg(float angleRad) {
  return angleRad*180.0/PI;
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
float analogToAngle(int analog_value){
  return (analog_value - 60.0)*(270.0/(pulsemin-60.0));
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
void readAngles(std_msgs::Float64MultiArray feedback_data){
  for(int i=0;i<12;i++){
    feedback_data.data[i] = analogToAngle(analogRead(analog_pins[i]));
  }
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
void subscriberCallback(const std_msgs::Float64MultiArray& cmd_msg) {

  float ros_motor_commands[12];
  
  for (int i = 0; i < 12; i++){
    ros_motor_commands[i] = radToDeg(cmd_msg.data[i]);
  }
  moveMotor(ros_motor_commands);
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
void moveMotor(float cmdAngle[12]) {
  float compensatedCmd[12];
  int pulseCmd[12];

  for (int i = 0; i < 12; i++) {
    compensatedCmd[i] = compensateCommand(cmdAngle[i], i);
    pulseCmd[i] = degToPulse(compensatedCmd[i]);
  }
  motorController(pulseCmd);
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
float compensateCommand(float rawAngle, int index) {
  return rawAngle + compensationArrayMec[index] + compensationArrayROS[index];
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radian
 * @return fdsafdsafdsa
 */
void motorController(int pulseCommand[12]) {

    for (int i = 0; i < 12; i++){
        if(pulseCommand[i] > jointLimit[i][1]){
            pulseCommand[i] = jointLimit[i][1];
          }
        else if(pulseCommand[i] < jointLimit[i][0]){
            pulseCommand[i] = jointLimit[i][0];
          }
      }
    
    for (int i=0; i < 12; i++){
        driver.writeMicroseconds(i, pulseCommand[i]);
    }
}