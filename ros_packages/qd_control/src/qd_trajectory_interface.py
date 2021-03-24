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
import threading

class Leg:
    def __init__(self, ID):
        self.ID = ID
        self.hip_id = ('J' + str( (self.ID - 1)*3 + 1 ) )
        self.upperleg_id = ('J' + str( (self.ID - 1)*3 + 2 ) )
        self.lowerleg_id = ('J' + str( (self.ID - 1)*3 + 3 ) )

        self.jta = actionlib.SimpleActionClient('/quadrus/leg_controller/follow_joint_trajectory', FollowJointTrajectoryAction)
        rospy.loginfo('Waiting for joint trajectory action')
        self.jta.wait_for_server()
        rospy.loginfo('Found joint trajectory action')

    def move_leg(self, angles):
        goal = FollowJointTrajectoryGoal()
        goal.trajectory.joint_names = [self.hip_id, self.upperleg_id, self.lowerleg_id]
        
        point = JointTrajectoryPoint()
        point.positions = angles
        point.time_from_start = rospy.Duration(0.5)
        goal.trajectory.points.append(point)
        self.jta.send_goal_and_wait(goal)

def push_up_sequence(leg_obj):
    leg_obj.move_leg([0, -0.78, 0])
    leg_obj.move_leg([0, 0, -1.0])
    leg_obj.move_leg([0, -0.78, 0])

def main():
    #legs = [Leg(1), Leg(2), Leg(3), Leg(4)]
    joints = ['J1', 'J2', 'J3', 'J4', 'J5', 'J6', 'J7', 'J8', 'J9', 'J10', 'J11', 'J12']

    for leg in legs:
        seq_thread = threading.Thread(target = push_up_sequence, args = (leg,))
    
if __name__ == '__main__':
    rospy.init_node('joint_position_tester')
    main()