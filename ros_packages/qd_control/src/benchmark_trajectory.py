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


def move(jta, angle):
    goal = FollowJointTrajectoryGoal()
    goal.trajectory.joint_names = ['J1']
    
    point = JointTrajectoryPoint()
    point.positions = [angle]
    point.time_from_start = rospy.Duration(1)
    goal.trajectory.points.append(point)
    jta.send_goal_and_wait(goal)
    
if __name__ == '__main__':
    rospy.init_node('joint_position_tester')

    jta = actionlib.SimpleActionClient('/quadrus/leg_controller/follow_joint_trajectory', FollowJointTrajectoryAction)
    rospy.loginfo('Waiting for joint trajectory action')
    jta.wait_for_server()
    rospy.loginfo('Found joint trajectory action')
    
    try:
        while(True):
            move(jta, 0)
            rospy.loginfo('Sent cmd to 0')
            time.sleep(5)
            move(jta, 1.5708)
            rospy.loginfo('Sent cmd to pi/2')
            time.sleep(5)
    except KeyboardInterrupt as e:
        print(e)