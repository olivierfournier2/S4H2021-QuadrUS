# S4H2021-QuadrUS

## System requirements
- Ubuntu 20.04 LTS

## ROS installation (Development environment)
- ROS Noetic Ninjemys:  [Installation documentation](http://wiki.ros.org/noetic/Installation/Ubuntu)
- Gazebo/Rviz : Choose Desktop-Full Install option when installing ROS
- Install Terminator

    ```
    sudo apt-get update
    ```
    ```
    sudo apt-get install terminator

## To set up this ROS project
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

## Launching 2D and 3D simulations
- Start by launching terminator and splitting into two terminals (T1 and T2)

- Launch roscore, the main ros node in T1:
    ```
    roscore 
    ```
    
- To view the robot model in Rviz, execute the following command in T2: 
    ```
    roslaunch simulation quadrus_rviz.launch
    ```

- To start the dynamic simulation in Gazebo, execute the following command in T2:
    ```
    roslaunch simulation quadrus_gazebo.launch
    ```

