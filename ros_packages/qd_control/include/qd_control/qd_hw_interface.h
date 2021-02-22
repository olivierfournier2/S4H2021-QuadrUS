#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/robot_hw.h>
#include <joint_limits_interface/joint_limits.h>
#include <joint_limits_interface/joint_limits_interface.h>
#include <controller_manager/controller_manager.h>
#include <boost/scoped_ptr.hpp>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>

class Quadrus : public hardware_interface::RobotHW 
{
    public:
        Quadrus(ros::NodeHandle& nh);                                                                   //Constructor
        ~Quadrus();                                                                                     //Destructor
        void init();                                                                                    //define all joint handle, joint's interfaces and joint limits interfaces
        void update(const ros::TimerEvent& e);                                                          //control loop()
        void read();                                                                                    //reading joint sensor data
        void write(ros::Duration elapsed_time);                                                         //sending command to motors
        
    protected:
        //Declare the type of joint interfaces and joint limit interfaces your robot actuators/motors are using.
        hardware_interface::JointStateInterface joint_state_interface_;
        hardware_interface::PositionJointInterface position_joint_interface_;
        
        joint_limits_interface::JointLimits limits;
        joint_limits_interface::PositionJointSaturationInterface positionJointSaturationInterface;
        
        const static int jnt_nb = 1;
        double pos[jnt_nb];
        double vel[jnt_nb];
        double eff[jnt_nb];
        double cmd[jnt_nb];

        ros::Publisher position_pub;
        
        ros::NodeHandle nh_;
        ros::Timer qd_control_loop_;
        ros::Duration elapsed_time_;
        double loop_hz_;
        boost::shared_ptr<controller_manager::ControllerManager> controller_manager_;
};