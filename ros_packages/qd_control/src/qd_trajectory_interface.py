#! /usr/bin/env python3

import roslib
#roslib.load_manifest('joint_trajectory_test')
import rospy
import actionlib
from std_msgs.msg import Float64
import trajectory_msgs.msg
import control_msgs.msg
from trajectory_msgs.msg import JointTrajectoryPoint
from control_msgs.msg import JointTrajectoryAction, JointTrajectoryGoal, FollowJointTrajectoryAction, FollowJointTrajectoryGoal
import time


def move(jta, angles):
    goal = FollowJointTrajectoryGoal()
    goal.trajectory.joint_names = ['J1', 'J2', 'J3', 'J4', 'J5', 'J6', 'J7', 'J8', 'J9', 'J10', 'J11', 'J12']
    
    point = JointTrajectoryPoint()
    point.positions = angles
    point.time_from_start = rospy.Duration(0.5)
    goal.trajectory.points.append(point)
    jta.send_goal_and_wait(goal)
    
if __name__ == '__main__':
    rospy.init_node('joint_position_tester')

    jta = actionlib.SimpleActionClient('/quadrus/leg_controller/follow_joint_trajectory', FollowJointTrajectoryAction)
    rospy.loginfo('Waiting for joint trajectory action')
    jta.wait_for_server()
    rospy.loginfo('Found joint trajectory action')
    
    while not rospy.is_shutdown():
        move(jta, [0, -0.785, 0, 0, -0.785, 0, 0, -0.785, 0, 0, -0.785, 0] )
        rospy.loginfo('Sent cmd to 0')
        time.sleep(5)
        move(jta, [0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1])
        rospy.loginfo('Sent cmd to pi/2')
        time.sleep(5)
