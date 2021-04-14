#! /usr/bin/env python3

import rospy
from std_msgs.msg import String, Float64MultiArray
import geometry_msgs.msg
import math
import sys
import rospkg
rospack = rospkg.RosPack()
sys.path.append(rospack.get_path('qd_interface') + "/src")


def radToDeg(rad):
    for i in range(12):
        rad[i] = math.degrees(rad[i])

    return rad


def command_callback(commands):
    hw_commands = radToDeg(list(commands.data))
    #hw_commands = radToDeg([0, math.pi / 2, 0, math.pi / 4, 0, math.pi, 0, math.pi / 2, 0, math.pi / 4, 0, math.pi])
    hw_commands = str(hw_commands).translate(str.maketrans({',': '','(': '',')': ''}))

    f = open(rospack.get_path('qd_interface') + "/src/motorsCommands.txt", "w")
    f.write(hw_commands)
    f.close()

    #f = open(rospack.get_path('qd_interface') + "/src/motorsCommands.txt", "r")
    #print(f.read())
    #f.close()


def position_callback(positions):
    hw_positions = radToDeg(list(positions.data))
    hw_positions = str(hw_positions).translate(str.maketrans({',': '','(': '',')': ''}))

    f = open(rospack.get_path('qd_interface') + "/src/motorsPositions.txt", "w")
    f.write(hw_positions)
    f.close()

    #f = open(rospack.get_path('qd_interface') + "/src/motorsPositions.txt", "r")
    #print(f.read())
    #f.close()
    
def listener():
    rospy.init_node('qd_interface', anonymous=False)

    rospy.Subscriber("hw_cmd", Float64MultiArray, command_callback)
    rospy.Subscriber("hw_feedback", Float64MultiArray, position_callback)

    print("qu_interface Node Started")

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
