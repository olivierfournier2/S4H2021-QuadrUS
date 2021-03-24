# S4H2021-QuadrUS

### Quadruped Robot | UdeS-GRO
[![Build Status](https://www.travis-ci.com/olivierfournier2/S4H2021-QuadrUS.svg?branch=main)](https://www.travis-ci.com/olivierfournier2/S4H2021-QuadrUS) [![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com) [![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)


## Development environment 

### System requirements
- Ubuntu 20.04 LTS

### ROS installation (Development environment)
- ROS Noetic Ninjemys:  [Installation documentation](http://wiki.ros.org/noetic/Installation/Ubuntu)
- Gazebo/Rviz : Choose Desktop-Full Install option when installing ROS
- Install Terminator

    ```
    sudo apt-get update
    ```
    ```
    sudo apt-get install terminator

### To set up this ROS project
- Create and initialize a catkin workspace

    ```
    mkdir -p ~/quadrus_ws/src
    ```
    ```
    cd ~/quadrus_ws/src
    ```
    ```
    catkin_init_workspace
    ```

- Clone the git repository into the src folder

    ```
    git clone --recurse-submodules https://github.com/olivierfournier2/S4H2021-QuadrUS.git
    ```

- Build the ROS workspace
    ```
    cd ~/quadrus_ws
    ```

    ```
    catkin_make
    ```

    ```
    . ~/quadrus_ws/devel/setup.bash
    ```

At this point, the ROS environment should be set up and ready to work with.

### Launching 2D and 3D simulations
- Start by launching terminator and splitting into two terminals (T1 and T2)

- Launch roscore, the main ros node in T1:
    ```
    roscore 
    ```
    
- To view the robot model in Rviz, execute the following command in T2: 
    ```
    roslaunch qd_simulation qd_rviz.launch
    ```

- To start the dynamic simulation in Gazebo, execute the following command in T2:
    ```
    roslaunch qd_simulation qd_gazebo.launch
    ```

## Robot environment

### System Requirements
- RaspberryPi 4
- Ubuntu 20.04.2 LTS, 64 bit

### ROS installation
- ROS Noetic Ninjemys:  [Installation documentation](http://wiki.ros.org/noetic/Installation/Ubuntu)

### Network setup
- Set up raspberry pi as access point: [Procedure](https://gist.github.com/ExtremeGTX/ea1d1c12dde8261b263ab2fead983dc8), [dnsmasq configuration](https://computingforgeeks.com/install-and-configure-dnsmasq-on-ubuntu-18-04-lts/)
- To allow ssh over wired connection, you need to set up static ip adress for both devices: [Procedure](https://linuxize.com/post/how-to-configure-static-ip-address-on-ubuntu-20-04/)



