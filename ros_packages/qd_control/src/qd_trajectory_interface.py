#! /usr/bin/env python3

import roslib
#roslib.load_manifest('joint_trajectory_test')
import rospy
import actionlib
from std_msgs.msg import Float64MultiArray
import trajectory_msgs.msg
import control_msgs.msg
from trajectory_msgs.msg import JointTrajectoryPoint
from control_msgs.msg import JointTrajectoryAction, JointTrajectoryGoal, FollowJointTrajectoryAction, FollowJointTrajectoryGoal
import time

def callback(data, jta):
    move(jta, data.data)
    rospy.loginfo('Sent cmd to joint_angles')

def move(jta, angles):
    goal = FollowJointTrajectoryGoal()
    goal.trajectory.joint_names = ['J1', 'J2', 'J3', 'J4', 'J5', 'J6', 'J7', 'J8', 'J9', 'J10', 'J11', 'J12']
    
    point = JointTrajectoryPoint()
    point.positions = angles
    point.time_from_start = rospy.Duration(0.1)
    goal.trajectory.points.append(point)
    jta.send_goal_and_wait(goal)
    
if __name__ == '__main__':
    rospy.init_node('qd_trajectory_interface')

    jta = actionlib.SimpleActionClient('/quadrus/leg_controller/follow_joint_trajectory', FollowJointTrajectoryAction)
    rospy.loginfo('Waiting for joint trajectory action')
    jta.wait_for_server()
    rospy.loginfo('Found joint trajectory action')
    
    rospy.Subscriber("joint_angles", Float64MultiArray, callback,jta)
    rospy.spin()
    

