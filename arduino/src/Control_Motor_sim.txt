
#include <ros.h>
#include <std_msgs/Float64MultiArray.h>

void CmdCallback( const std_msgs::Float64MultiArray& cmd_data){
  for(int i=0 ; i<12 ; i++){
    //Send cmd to motor
  }
}

float AnalogToAngle(int analog_value){
  float angle = 0;
  angle = map(analog_value, 0,1023, 0, 270.0);
  return angle;
}

void readAngles(std_msgs::Float64MultiArray feedback_data){
   for(int i=0 ; i<12 ; i++){
    feedback_data.data[i] = AnalogToAngle(analogRead(A0));
  }
}


ros::NodeHandle  nh;
std_msgs::Float64MultiArray feedback_data;
ros::Publisher feedback_pub("hw_feedback", &feedback_data);
ros::Subscriber<std_msgs::Float64MultiArray> cmd_sub("hw_cmd", CmdCallback );

void setup()
{
  nh.getHardware()->setBaud(230400);
  nh.initNode();
  nh.advertise(feedback_pub);
  feedback_data.data_length = 12;
  feedback_data.data = (float *)malloc(sizeof(float) *12);
  nh.subscribe(cmd_sub);
}

void loop()
{
  readAngles(feedback_data);
  feedback_pub.publish( &feedback_data );
  nh.spinOnce();
  delay(5);
}
