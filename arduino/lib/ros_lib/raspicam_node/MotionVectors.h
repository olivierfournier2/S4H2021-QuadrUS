#ifndef _ROS_raspicam_node_MotionVectors_h
#define _ROS_raspicam_node_MotionVectors_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace raspicam_node
{

  class MotionVectors : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint8_t _mbx_type;
      _mbx_type mbx;
      typedef uint8_t _mby_type;
      _mby_type mby;
      uint32_t x_length;
      typedef int8_t _x_type;
      _x_type st_x;
      _x_type * x;
      uint32_t y_length;
      typedef int8_t _y_type;
      _y_type st_y;
      _y_type * y;
      uint32_t sad_length;
      typedef uint16_t _sad_type;
      _sad_type st_sad;
      _sad_type * sad;

    MotionVectors():
      header(),
      mbx(0),
      mby(0),
      x_length(0), st_x(), x(nullptr),
      y_length(0), st_y(), y(nullptr),
      sad_length(0), st_sad(), sad(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->mbx >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mbx);
      *(outbuffer + offset + 0) = (this->mby >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mby);
      *(outbuffer + offset + 0) = (this->x_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->x_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->x_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->x_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x_length);
      for( uint32_t i = 0; i < x_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_xi;
      u_xi.real = this->x[i];
      *(outbuffer + offset + 0) = (u_xi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->x[i]);
      }
      *(outbuffer + offset + 0) = (this->y_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->y_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->y_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->y_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_length);
      for( uint32_t i = 0; i < y_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_yi;
      u_yi.real = this->y[i];
      *(outbuffer + offset + 0) = (u_yi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->y[i]);
      }
      *(outbuffer + offset + 0) = (this->sad_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->sad_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->sad_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->sad_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sad_length);
      for( uint32_t i = 0; i < sad_length; i++){
      *(outbuffer + offset + 0) = (this->sad[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->sad[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->sad[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->mbx =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mbx);
      this->mby =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mby);
      uint32_t x_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      x_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      x_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      x_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->x_length);
      if(x_lengthT > x_length)
        this->x = (int8_t*)realloc(this->x, x_lengthT * sizeof(int8_t));
      x_length = x_lengthT;
      for( uint32_t i = 0; i < x_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_st_x;
      u_st_x.base = 0;
      u_st_x.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->st_x = u_st_x.real;
      offset += sizeof(this->st_x);
        memcpy( &(this->x[i]), &(this->st_x), sizeof(int8_t));
      }
      uint32_t y_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      y_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      y_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      y_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->y_length);
      if(y_lengthT > y_length)
        this->y = (int8_t*)realloc(this->y, y_lengthT * sizeof(int8_t));
      y_length = y_lengthT;
      for( uint32_t i = 0; i < y_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_st_y;
      u_st_y.base = 0;
      u_st_y.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->st_y = u_st_y.real;
      offset += sizeof(this->st_y);
        memcpy( &(this->y[i]), &(this->st_y), sizeof(int8_t));
      }
      uint32_t sad_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      sad_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      sad_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      sad_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->sad_length);
      if(sad_lengthT > sad_length)
        this->sad = (uint16_t*)realloc(this->sad, sad_lengthT * sizeof(uint16_t));
      sad_length = sad_lengthT;
      for( uint32_t i = 0; i < sad_length; i++){
      this->st_sad =  ((uint16_t) (*(inbuffer + offset)));
      this->st_sad |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->st_sad);
        memcpy( &(this->sad[i]), &(this->st_sad), sizeof(uint16_t));
      }
     return offset;
    }

    virtual const char * getType() override { return "raspicam_node/MotionVectors"; };
    virtual const char * getMD5() override { return "f3b1d1ffbb5afc62c85d36a98f659ddf"; };

  };

}
#endif
