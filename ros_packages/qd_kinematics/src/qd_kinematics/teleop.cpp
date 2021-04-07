#include "qd_kinematics/teleop.hpp"

namespace tele
{
	Teleop::Teleop(const int & linear_x, const int & linear_y, const int & linear_z,
	               const int & angular, const double & l_scale, const double & a_scale,
	               const int & LB, const int & RB, const int & B_scale, const int & LT,
	               const int & RT, const int & UD, const int & LR,
	               const int & sw, const int & es, ros::NodeHandle* nh, tele::Teleop &teleop)
	{
		// step length or pitch
		linear_x_ = linear_x;
		// lateral fraction or roll
		linear_y_ = linear_y;
		// height
		linear_z_ = linear_z;
		// yaw rate or yaw
		angular_ = angular;
		// scale linear axis (usually just 1)
		l_scale_ = l_scale;
		// scale angular axis (usually just 1)
		a_scale_ = a_scale;
		// for incrementing and decrementing step velocity
		// Bottom Bumpers
		RB_ = RB;
		LB_ = LB;
		// scale Bottom Trigger axis (usually just 1)
		B_scale_ = B_scale;
		// Top Bumpers
		RT_ = RT;
		LT_ = LT;
		// Switch between Stepping and Viewing
		sw_ = sw;
		// E-STOP
		es_ = es;

		// Arrow PAd
		UD_ = UD;
		LR_ = LR;

		switch_trigger = false;
		ESTOP = false;
		ready2pressES = true;
		ready2pressSW = true;
		updown = 0;
        leftright = 0;

		left_bump = false;
		right_bump = false;
		for (int i = 0; i < 6; i++)
		{
			current_cmd[i] = 0;
		}
		// Set publisher and subscriber
		// Init ESTOP Publisher
		estop_pub = nh->advertise<std_msgs::Bool>("estop", 1);
		// Init Command Publisher
		vel_pub = nh->advertise<geometry_msgs::Twist>("teleop", 1);
		// Init Joy Button Publisher
		jb_pub = nh->advertise<qd_kinematics::JoyButtons>("joybuttons", 1);
		// Init Subscriber (also handles pub)
		joy_sub = nh->subscribe<sensor_msgs::Joy>("joy", 1, &tele::Teleop::joyCallback, &teleop);
		// Init Switch Movement Server
		switch_movement_client = nh->serviceClient<std_srvs::Empty>("switch_movement");
    	ros::service::waitForService("switch_movement", -1);
	}

	void Teleop::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
	{
		sendCommandVel(joy);

		// Switch Trigger: Button A
		switch_trigger = joy->buttons[sw_];

		// ESTOP: Button B
		ESTOP = joy->buttons[es_];

		// Arrow Pad
		updown = joy->axes[UD_];
		leftright = -joy->axes[LR_];

		// Top Bumpers
		left_bump = joy->buttons[LT_];
		right_bump = joy->buttons[RT_];

        std_msgs::Bool estop;
        estop.data = return_estop();
		if (estop.data and ready2pressES == true)
		{
			ROS_INFO("SENDING E-STOP COMMAND!");
			ready2pressES = false;
		} else if (estop.data and ready2pressES == false)
		{
			estop.data = 0;
		} else if (!estop.data and ready2pressES == false)
		{
			ready2pressES = true;
		}

		estop_pub.publish(estop);

		// Call Switch Service
		if (return_trigger() and ready2pressSW == true) {
			std_srvs::Empty e;
			switch_movement_client.call(e);
			estop.data = 0;
			ready2pressSW = false;
		} else if (!return_trigger() and ready2pressSW == false)
		{
			ready2pressSW = true;
		}

        // pub buttons
        jb_pub.publish(return_buttons());        
	}

	void Teleop::sendCommandVel(const sensor_msgs::Joy::ConstPtr& joy) {
		double tol_step[6] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01};
		double true_step[6] = {0,0,0,0,0,0};
		double cmd_vel_ramped[6];

		cmd_vel_ramped[0] = l_scale_*joy->axes[linear_x_];
		cmd_vel_ramped[1] = l_scale_*joy->axes[linear_y_];
		// NOTE: used to control robot height
		cmd_vel_ramped[2] = -l_scale_*joy->axes[linear_z_];
		cmd_vel_ramped[3] = a_scale_*joy->axes[angular_];
		// NOTE: bottom bumpers used for changing step velocity
		cmd_vel_ramped[4] = B_scale_*joy->axes[RB_];
		cmd_vel_ramped[5] = B_scale_*joy->axes[LB_];


		for (int i = 0; i < 6; i++)
		{
			if (cmd_vel_ramped[i] > current_cmd[i]){
			true_step[i] = cmd_vel_ramped[i] - current_cmd[i];
			
			if (true_step[i] > tol_step[i]){
				current_cmd[i] += tol_step[i];
			}
			else{
				current_cmd[i] += true_step[i];
			}
			}
			else if (cmd_vel_ramped[i] < current_cmd[i]){
			true_step[i] = current_cmd[i] - cmd_vel_ramped[i];
			
			if (true_step[i] > tol_step[i]){
				current_cmd[i] -= tol_step[i];
			}
			else{
				current_cmd[i] -= true_step[i];
			}
			}
		}

		twist.linear.x = current_cmd[0];
		twist.linear.y = current_cmd[1];
		twist.linear.z = current_cmd[2];
		twist.angular.z = current_cmd[3];
		twist.angular.y = current_cmd[4];
		twist.angular.x = current_cmd[5];

		vel_pub.publish(return_twist());
	}

	geometry_msgs::Twist Teleop::return_twist()
	{
		return twist;
	}

	bool Teleop::return_trigger()
	{
		return switch_trigger;
	}

	bool Teleop::return_estop()
	{
		return ESTOP;
	}

	qd_kinematics::JoyButtons Teleop::return_buttons()
	{
		qd_kinematics::JoyButtons jb;
		jb.updown = updown;
		jb.leftright = leftright;
		jb.left_bump = left_bump;
		jb.right_bump = right_bump;

		return jb;
	}	
}
