#!/bin/bash

export ROS_MASTER_URI=http://localhost:11311/
export ROS_IP="localhost"
export ROSLAUNCH_SSH_UNKNOWN=1

source /opt/ros/noetic/setup.bash
source ~/quadrus_ws/devel/setup.bash

exec "$@"-