/// \file
/// \brief Draws Each Obstacle in RViz using MarkerArrays
///
/// PARAMETERS:
/// PUBLISHES:
/// SUBSCRIBES:
/// FUNCTIONS:

#include <ros/ros.h>

#include <math.h>
#include <string>
#include <vector>

#include <qd_kinematics/spot.hpp>
#include <qd_kinematics/teleop.hpp>
#include "qd_kinematics/MiniCmd.h"
#include "std_msgs/Bool.h"
#include "std_srvs/Empty.h"
#include "qd_kinematics/JoyButtons.h"

#include <functional>  // To use std::bind


int main(int argc, char** argv)
/// The Main Function ///
{
    ROS_INFO("STARTING NODE: Teleoperation");

    // Vars
    double frequency = 60;
    int linear_x = 4;
    int linear_y = 3;
    int linear_z = 1;
    int angular = 0;
    int sw = 0;
    int es = 1;
    int RB = 5;
    int LB = 2;
    int RT = 5;
    int LT = 4;
    int UD = 7;
    int LR = 6;
    double l_scale = 1.0;
    double a_scale = 1.0;
    double B_scale = 1.0;
    double debounce_thresh = 0.15; // sec

    ros::init(argc, argv, "teleop_node"); // register the node on ROS
    ros::NodeHandle nh; // get a handle to ROS
    ros::NodeHandle nh_("~"); // get a handle to ROS
    // Parameters
    nh_.getParam("frequency", frequency);
    nh_.getParam("axis_linear_x", linear_x);
    nh_.getParam("axis_linear_y", linear_y);
    nh_.getParam("axis_linear_z", linear_z);
    nh_.getParam("axis_angular", angular);
    nh_.getParam("scale_linear", l_scale);
    nh_.getParam("scale_angular", a_scale);
    nh_.getParam("scale_bumper", B_scale);
    nh_.getParam("button_switch", sw);
    nh_.getParam("button_estop", es);
    nh_.getParam("rb", RB);
    nh_.getParam("lb", LB);
    nh_.getParam("rt", RT);
    nh_.getParam("lt", LT);
    nh_.getParam("updown", UD);
    nh_.getParam("leftright", LR);
    nh_.getParam("debounce_thresh", debounce_thresh);

    tele::Teleop teleop = tele::Teleop(linear_x, linear_y, linear_z, angular,
                                       l_scale, a_scale, LB, RB, B_scale, LT,
                                       RT, UD, LR, sw, es, &nh, teleop);
    
    ros::spin();

    return 0;
}
