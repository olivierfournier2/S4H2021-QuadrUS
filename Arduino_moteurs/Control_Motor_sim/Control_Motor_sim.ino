
#include <ros.h>
#include <std_msgs/Float64MultiArray.h>

ros::NodeHandle  nh;

void CmdCallback( const std_msgs::Float64MultiArray& cmd_data){
  for(int i=0 ; i<12 ; i++){
    delay(1);
  }
}

std_msgs::Float64MultiArray feedback_data;
ros::Publisher feedback_pub("hw_feedback", &feedback_data);
ros::Subscriber<std_msgs::Float64MultiArray> cmd_sub("hw_cmd", CmdCallback );

void setup()
{
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(feedback_pub);
  nh.subscribe(cmd_sub);
}

void loop()
{
  //for(int i=0 ; i<12 ; i++){
  //  feedback_data.data[i] = random(1, 100)/100.0;
  //}
  feedback_pub.publish( &feedback_data );
  nh.spinOnce();
  delay(500);
}
