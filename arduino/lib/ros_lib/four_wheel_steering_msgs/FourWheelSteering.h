#ifndef _ROS_four_wheel_steering_msgs_FourWheelSteering_h
#define _ROS_four_wheel_steering_msgs_FourWheelSteering_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace four_wheel_steering_msgs
{

  class FourWheelSteering : public ros::Msg
  {
    public:
      typedef float _front_steering_angle_type;
      _front_steering_angle_type front_steering_angle;
      typedef float _rear_steering_angle_type;
      _rear_steering_angle_type rear_steering_angle;
      typedef float _front_steering_angle_velocity_type;
      _front_steering_angle_velocity_type front_steering_angle_velocity;
      typedef float _rear_steering_angle_velocity_type;
      _rear_steering_angle_velocity_type rear_steering_angle_velocity;
      typedef float _speed_type;
      _speed_type speed;
      typedef float _acceleration_type;
      _acceleration_type acceleration;
      typedef float _jerk_type;
      _jerk_type jerk;

    FourWheelSteering():
      front_steering_angle(0),
      rear_steering_angle(0),
      front_steering_angle_velocity(0),
      rear_steering_angle_velocity(0),
      speed(0),
      acceleration(0),
      jerk(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_front_steering_angle;
      u_front_steering_angle.real = this->front_steering_angle;
      *(outbuffer + offset + 0) = (u_front_steering_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_front_steering_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_front_steering_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_front_steering_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->front_steering_angle);
      union {
        float real;
        uint32_t base;
      } u_rear_steering_angle;
      u_rear_steering_angle.real = this->rear_steering_angle;
      *(outbuffer + offset + 0) = (u_rear_steering_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rear_steering_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rear_steering_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rear_steering_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rear_steering_angle);
      union {
        float real;
        uint32_t base;
      } u_front_steering_angle_velocity;
      u_front_steering_angle_velocity.real = this->front_steering_angle_velocity;
      *(outbuffer + offset + 0) = (u_front_steering_angle_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_front_steering_angle_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_front_steering_angle_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_front_steering_angle_velocity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->front_steering_angle_velocity);
      union {
        float real;
        uint32_t base;
      } u_rear_steering_angle_velocity;
      u_rear_steering_angle_velocity.real = this->rear_steering_angle_velocity;
      *(outbuffer + offset + 0) = (u_rear_steering_angle_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rear_steering_angle_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rear_steering_angle_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rear_steering_angle_velocity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rear_steering_angle_velocity);
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
      union {
        float real;
        uint32_t base;
      } u_acceleration;
      u_acceleration.real = this->acceleration;
      *(outbuffer + offset + 0) = (u_acceleration.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acceleration.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_acceleration.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_acceleration.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->acceleration);
      union {
        float real;
        uint32_t base;
      } u_jerk;
      u_jerk.real = this->jerk;
      *(outbuffer + offset + 0) = (u_jerk.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_jerk.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_jerk.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_jerk.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->jerk);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_front_steering_angle;
      u_front_steering_angle.base = 0;
      u_front_steering_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_front_steering_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_front_steering_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_front_steering_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->front_steering_angle = u_front_steering_angle.real;
      offset += sizeof(this->front_steering_angle);
      union {
        float real;
        uint32_t base;
      } u_rear_steering_angle;
      u_rear_steering_angle.base = 0;
      u_rear_steering_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rear_steering_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rear_steering_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rear_steering_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rear_steering_angle = u_rear_steering_angle.real;
      offset += sizeof(this->rear_steering_angle);
      union {
        float real;
        uint32_t base;
      } u_front_steering_angle_velocity;
      u_front_steering_angle_velocity.base = 0;
      u_front_steering_angle_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_front_steering_angle_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_front_steering_angle_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_front_steering_angle_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->front_steering_angle_velocity = u_front_steering_angle_velocity.real;
      offset += sizeof(this->front_steering_angle_velocity);
      union {
        float real;
        uint32_t base;
      } u_rear_steering_angle_velocity;
      u_rear_steering_angle_velocity.base = 0;
      u_rear_steering_angle_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rear_steering_angle_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rear_steering_angle_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rear_steering_angle_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rear_steering_angle_velocity = u_rear_steering_angle_velocity.real;
      offset += sizeof(this->rear_steering_angle_velocity);
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
      union {
        float real;
        uint32_t base;
      } u_acceleration;
      u_acceleration.base = 0;
      u_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->acceleration = u_acceleration.real;
      offset += sizeof(this->acceleration);
      union {
        float real;
        uint32_t base;
      } u_jerk;
      u_jerk.base = 0;
      u_jerk.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_jerk.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_jerk.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_jerk.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->jerk = u_jerk.real;
      offset += sizeof(this->jerk);
     return offset;
    }

    virtual const char * getType() override { return "four_wheel_steering_msgs/FourWheelSteering"; };
    virtual const char * getMD5() override { return "04dd0f55e1f168668af1e2587a7cdd2a"; };

  };

}
#endif
