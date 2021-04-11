#!/bin/bash

export ROS_MASTER_URI=http://192.168.4.17:11311/
export ROS_IP="192.168.4.1"
export ROSLAUNCH_SSH_UNKNOWN=1

source /opt/ros/noetic/setup.bash
source ~/quadrus_ws/devel/setup.bash

exec "$@"-