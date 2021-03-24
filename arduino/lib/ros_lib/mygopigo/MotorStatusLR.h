#ifndef _ROS_mygopigo_MotorStatusLR_h
#define _ROS_mygopigo_MotorStatusLR_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "mygopigo/MotorStatus.h"

namespace mygopigo
{

  class MotorStatusLR : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef mygopigo::MotorStatus _left_type;
      _left_type left;
      typedef mygopigo::MotorStatus _right_type;
      _right_type right;

    MotorStatusLR():
      header(),
      left(),
      right()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->left.serialize(outbuffer + offset);
      offset += this->right.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->left.deserialize(inbuffer + offset);
      offset += this->right.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "mygopigo/MotorStatusLR"; };
    virtual const char * getMD5() override { return "924fb1e61934a72c1fa7cdf1620e9fa4"; };

  };

}
#endif
