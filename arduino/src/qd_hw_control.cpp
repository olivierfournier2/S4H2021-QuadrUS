#include "qd_hw_control.h"

/**
* Initialise node handle of ROS
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
 * Initialise the driver object to control the servos
 * from the PCA9685 board
 */
void servoInit(){
  driver.begin();
  driver.setOscillatorFrequency(27000000);
  driver.setPWMFreq(servo_freq);
}


/**
 * Compute the joint limits with the base angle of 135 degree
 * and the mechanical compensations
 */
void computeLimits() {
  for (int i = 0; i < 12; i++){
    for (int j = 0; j < 2; j++){
      jointLimit[i][j] =  degToPulse(135 + compensationArrayMec[i] + jointLimit[i][j]);
    }
  }
}


/**
 * Map an angle in degrees to the corresponding pulse
 *
 * @param ang Angle in degrees
 * @return Corresponding pulse
 */
int degToPulse(float ang) {
  int pulse = map(ang, 0, 270, pulsemin, pulsemax);
  return pulse;
}


/**
 * Convert an angle in rad to degrees
 *
 * @param angleRad Angle in rad
 * @return angle in degrees
 */
float radToDeg(float angleRad) {
  return angleRad*180.0/PI;
}

/**
 * Convert an angle in degrees to radians
 *
 * @param angleDeg Angle in deg
 * @return angle in rad
 */
float degToRad(float angleDeg) {
  return angleDeg*PI/180.0;
}

/**
 * Convert the analog output of a servo potentiometer to an angle in degrees
 *
 * @param analog_value Analog reading from Arduino
 * @return angle in degrees
 */
float analogToAngle(int analog_value){
  return (analog_value - 60.0)*(270.0/(pulsemin-60.0));
}


/**
 * Read the analog inputs on the Arduino and store them
 * in angle in the feedback_data to send back to ROS
 *
 * @param feedback_data Current angle of the servos to feedback to ROS
 */
void readAngles(std_msgs::Float64MultiArray feedback_data){
  for(int i=0;i<12;i++){
    feedback_data.data[i] = analogToAngle(analogRead(analog_pins[i]));
  }
}


/**
 * Receive angle commands from ROS and convert them to degrees
 *
 * @param cmd_msg ROS controller message specifying joint angle in radians
 */
void subscriberCallback(const std_msgs::Float64MultiArray& cmd_msg) {

  float ros_motor_commands[12];
  
  for (int i = 0; i < 12; i++){
    ros_motor_commands[i] = radToDeg(cmd_msg.data[i]);
  }
  moveMotor(ros_motor_commands);
}


/**
 * Receive angle commands, add the compensations,
 * convert them to pulse and move the motors
 *
 * @param cmdAngle Array of commands in degrees for the 12 motors
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
 * Add the mechanical and the ROS compensations to the angle command passed
 *
 * @param rawAngle Angle in degrees before adding compensations
 * @param index Index of the motor corresponding to the rawAngle passed
 * @return The angle command with the compensations
 */
float compensateCommand(float rawAngle, int index) {
  return rawAngle + compensationArrayMec[index] + compensationArrayROS[index];
}


/**
 * Check if the pulse commands are within the joint limits then write the commands
 * to the driver to move the motors one after the other
 *
 * @param pulseCommand Array of commands in pulse for the 12 motors
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