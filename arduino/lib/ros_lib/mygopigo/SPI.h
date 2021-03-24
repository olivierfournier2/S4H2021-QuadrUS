#ifndef _ROS_SERVICE_SPI_h
#define _ROS_SERVICE_SPI_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mygopigo
{

static const char SPI[] = "mygopigo/SPI";

  class SPIRequest : public ros::Msg
  {
    public:
      uint32_t data_out_length;
      typedef uint8_t _data_out_type;
      _data_out_type st_data_out;
      _data_out_type * data_out;

    SPIRequest():
      data_out_length(0), st_data_out(), data_out(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->data_out_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->data_out_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->data_out_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->data_out_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data_out_length);
      for( uint32_t i = 0; i < data_out_length; i++){
      *(outbuffer + offset + 0) = (this->data_out[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data_out[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t data_out_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      data_out_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      data_out_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      data_out_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->data_out_length);
      if(data_out_lengthT > data_out_length)
        this->data_out = (uint8_t*)realloc(this->data_out, data_out_lengthT * sizeof(uint8_t));
      data_out_length = data_out_lengthT;
      for( uint32_t i = 0; i < data_out_length; i++){
      this->st_data_out =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_data_out);
        memcpy( &(this->data_out[i]), &(this->st_data_out), sizeof(uint8_t));
      }
     return offset;
    }

    virtual const char * getType() override { return SPI; };
    virtual const char * getMD5() override { return "561ae924966a6e65b3e6723a081d160a"; };

  };

  class SPIResponse : public ros::Msg
  {
    public:
      uint32_t data_in_length;
      typedef uint8_t _data_in_type;
      _data_in_type st_data_in;
      _data_in_type * data_in;

    SPIResponse():
      data_in_length(0), st_data_in(), data_in(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->data_in_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->data_in_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->data_in_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->data_in_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data_in_length);
      for( uint32_t i = 0; i < data_in_length; i++){
      *(outbuffer + offset + 0) = (this->data_in[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data_in[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t data_in_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      data_in_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      data_in_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      data_in_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->data_in_length);
      if(data_in_lengthT > data_in_length)
        this->data_in = (uint8_t*)realloc(this->data_in, data_in_lengthT * sizeof(uint8_t));
      data_in_length = data_in_lengthT;
      for( uint32_t i = 0; i < data_in_length; i++){
      this->st_data_in =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_data_in);
        memcpy( &(this->data_in[i]), &(this->st_data_in), sizeof(uint8_t));
      }
     return offset;
    }

    virtual const char * getType() override { return SPI; };
    virtual const char * getMD5() override { return "a70bf8ea6ca66d7c5a18abead186e47d"; };

  };

  class SPI {
    public:
    typedef SPIRequest Request;
    typedef SPIResponse Response;
  };

}
#endif
