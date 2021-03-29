import rospy
from std_msgs import Float64


def callback(data):
    rospy.loginfo("I heard %s",data.data)
    
def listener():
    rospy.init_node('node_name')
    rospy.Subscriber("quadrus/joint_positions", String, callback)
    rospy.spin()


if __name__ == "__main__":

    pub = rospy.Publisher('topic_name', std_msgs.msg.String, queue_size=10)

