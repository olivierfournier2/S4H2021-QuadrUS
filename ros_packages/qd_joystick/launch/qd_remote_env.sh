#!/bin/bash

export ROS_MASTER_URI=http://ubuntudev-XPS-15-9550:11311/
export ROS_HOSTNAME=pi_quadrus

source /opt/ros/noetic/setup.bash
source ~/quadrus_ws/devel/setup.bash

exec "$@"