import rospy
from std_msgs import Float64
from sensor_msgs import JointStates

rospy.Timer()

def callback(data, pub):
    pub.
    
    
    
    

if __name__ == "__main__":

    pub = rospy.Publisher('gazebo_benchmark_angle', 
                          std_msgs.msg.Float64, 
                          queue_size=100)

    rospy.init_node('angle_publisher')
    rospy.Subscriber("quadrus/joint_positions", JointStates, callback, (pub,))
    rospy.spin()

    

