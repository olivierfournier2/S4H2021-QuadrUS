#ifndef _ROS_four_wheel_steering_msgs_FourWheelSteeringStamped_h
#define _ROS_four_wheel_steering_msgs_FourWheelSteeringStamped_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "four_wheel_steering_msgs/FourWheelSteering.h"

namespace four_wheel_steering_msgs
{

  class FourWheelSteeringStamped : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef four_wheel_steering_msgs::FourWheelSteering _data_type;
      _data_type data;

    FourWheelSteeringStamped():
      header(),
      data()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->data.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->data.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "four_wheel_steering_msgs/FourWheelSteeringStamped"; };
    virtual const char * getMD5() override { return "9226582df815bc6df9e3206bc05923af"; };

  };

}
#endif
