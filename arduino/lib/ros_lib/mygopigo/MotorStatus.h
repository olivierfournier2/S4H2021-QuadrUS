#ifndef _ROS_mygopigo_MotorStatus_h
#define _ROS_mygopigo_MotorStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mygopigo
{

  class MotorStatus : public ros::Msg
  {
    public:
      typedef bool _low_voltage_type;
      _low_voltage_type low_voltage;
      typedef bool _overloaded_type;
      _overloaded_type overloaded;
      typedef int8_t _power_type;
      _power_type power;
      typedef float _encoder_type;
      _encoder_type encoder;
      typedef float _speed_type;
      _speed_type speed;

    MotorStatus():
      low_voltage(0),
      overloaded(0),
      power(0),
      encoder(0),
      speed(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_low_voltage;
      u_low_voltage.real = this->low_voltage;
      *(outbuffer + offset + 0) = (u_low_voltage.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->low_voltage);
      union {
        bool real;
        uint8_t base;
      } u_overloaded;
      u_overloaded.real = this->overloaded;
      *(outbuffer + offset + 0) = (u_overloaded.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->overloaded);
      union {
        int8_t real;
        uint8_t base;
      } u_power;
      u_power.real = this->power;
      *(outbuffer + offset + 0) = (u_power.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->power);
      union {
        float real;
        uint32_t base;
      } u_encoder;
      u_encoder.real = this->encoder;
      *(outbuffer + offset + 0) = (u_encoder.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_encoder.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_encoder.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_encoder.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->encoder);
      union {
        float real;
        uint32_t base;
      } u_speed;
      u_speed.real = this->speed;
      *(outbuffer + offset + 0) = (u_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->speed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_low_voltage;
      u_low_voltage.base = 0;
      u_low_voltage.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->low_voltage = u_low_voltage.real;
      offset += sizeof(this->low_voltage);
      union {
        bool real;
        uint8_t base;
      } u_overloaded;
      u_overloaded.base = 0;
      u_overloaded.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->overloaded = u_overloaded.real;
      offset += sizeof(this->overloaded);
      union {
        int8_t real;
        uint8_t base;
      } u_power;
      u_power.base = 0;
      u_power.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->power = u_power.real;
      offset += sizeof(this->power);
      union {
        float real;
        uint32_t base;
      } u_encoder;
      u_encoder.base = 0;
      u_encoder.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_encoder.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_encoder.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_encoder.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->encoder = u_encoder.real;
      offset += sizeof(this->encoder);
      union {
        float real;
        uint32_t base;
      } u_speed;
      u_speed.base = 0;
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->speed = u_speed.real;
      offset += sizeof(this->speed);
     return offset;
    }

    virtual const char * getType() override { return "mygopigo/MotorStatus"; };
    virtual const char * getMD5() override { return "fa9d221cf281ffba79b583b9dd588c6f"; };

  };

}
#endif
