#! /usr/bin/env python3

import rospy
import actionlib
from std_msgs.msg import Float64MultiArray
import trajectory_msgs.msg
import control_msgs.msg
from trajectory_msgs.msg import JointTrajectoryPoint
from control_msgs.msg import JointTrajectoryAction, JointTrajectoryGoal, FollowJointTrajectoryAction, FollowJointTrajectoryGoal

rate = 0
qd_joint_names = ['J1', 'J2', 'J3', 
                  'J4', 'J5', 'J6',
                  'J7', 'J8', 'J9',
                  'J10', 'J11', 'J12']

def cmdCallback(data, jta):
    move(jta, data.data)

def move(jta, angles):
    
    # Create new trajectory point, set angles and execution time
    tj_point = JointTrajectoryPoint()
    tj_point.positions = angles
    tj_point.time_from_start = rospy.Duration(1/rate)

    # Create a trajectory goal, set joint names and add points
    goal = FollowJointTrajectoryGoal()
    goal.trajectory.joint_names = qd_joint_names
    goal.trajectory.points.append(tj_point)

    jta.send_goal(goal)

if __name__ == '__main__':
    rospy.init_node('qd_trajectory_interface')

    jta = actionlib.SimpleActionClient('/quadrus/leg_controller/follow_joint_trajectory', FollowJointTrajectoryAction)
    rospy.loginfo('Waiting for joint trajectory action')
    jta.wait_for_server()
    rospy.loginfo('Found joint trajectory action')
    
    rospy.Subscriber("joint_angles", Float64MultiArray, cmdCallback, jta, queue_size=10)
    rate = rospy.get_param("/quadrus/control_rate")
    rospy.spin()

