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

class Leg:
    def __init__(self, leg_name):
        self.name = leg_name
        self.hip = Joint('joint_' + self.name + '_hip')
        self.upperleg = Joint('joint_' + self.name + '_upperleg')
        self.lowerleg = Joint('joint_' + self.name + '_lowerleg')

        self.jta = actionlib.SimpleActionClient('/quadrus/leg_' + self.name + '_controller/follow_joint_trajectory', FollowJointTrajectoryAction)
        rospy.loginfo('Waiting for joint trajectory action')
        self.jta.wait_for_server()
        rospy.loginfo('Found joint trajectory action')

    def move_leg(self, angles):
        goal = FollowJointTrajectoryGoal()
        goal.trajectory.joint_names = ['joint_' + self.name + '_hip', 'joint_' + self.name + '_upperleg', 'joint_' + self.name + '_lowerleg']
        
        point = JointTrajectoryPoint()
        point.positions = angles
        point.time_from_start = rospy.Duration(0.5)
        goal.trajectory.points.append(point)
        self.jta.send_goal_and_wait(goal)

class Joint:
    def __init__(self, motor_name):
        self.name = motor_name


def main():
    legs = [Leg('back_right')]
    legs[0].move_leg([0, 0, 0])
    legs[0].move_leg([0, -0.5, -0.2])
    legs[0].move_leg([0, -0.6, 0.2])
    legs[0].move_leg([0, 0, 0])

if __name__ == '__main__':
    rospy.init_node('joint_position_tester')
    main()