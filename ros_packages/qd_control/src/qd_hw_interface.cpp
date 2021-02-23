#include <qd_control/qd_hw_interface.h>

Quadrus::Quadrus(ros::NodeHandle& nh): nh_(nh){

    init();

    controller_manager_.reset(new controller_manager::ControllerManager(this, nh_));

    loop_hz_ = 10;
    ros::Duration update_freq = ros::Duration(1.0/loop_hz_);

    qd_control_loop_ = nh_.createTimer(update_freq, &Quadrus::update, this);

    position_pub = nh.advertise<std_msgs::Float64MultiArray>("joint_positions", 1000);
}   
                                                   
Quadrus::~Quadrus(){
    delete[] jsHandle;
    delete[] jpHandle;
}   

void Quadrus::init(){
        
    for(int i = 0;i<jnt_nb;i++){
    
        jsHandle[i] = new hardware_interface::JointStateHandle(("J" + std::to_string(i+1)), &pos[i], &vel[i], &eff[i]);
        joint_state_interface_.registerHandle(*jsHandle[i]);

        jpHandle[i] = new hardware_interface::JointHandle(joint_state_interface_.getHandle(("J" + std::to_string(i+1))), &cmd[i]);
        position_joint_interface_.registerHandle(*jpHandle[i]);
    }

    registerInterface(&joint_state_interface_);
    registerInterface(&position_joint_interface_);


    //hardware_interface::JointStateHandle jointStateHandle("TestJoint", &pos[0], &vel[0], &eff[0]);
    //joint_state_interface_.registerHandle(jointStateHandle);

    //hardware_interface::JointHandle jointPositionHandle(joint_state_interface_.getHandle("TestJoint"), &cmd[0]);
    //position_joint_interface_.registerHandle(jointPositionHandle);

    //joint_limits_interface::getJointLimits("TestJoint", nh_, limits);
    //joint_limits_interface::PositionJointSaturationHandle jointLimitsHandle(jointPositionHandle, limits);
    //positionJointSaturationInterface.registerHandle(jointLimitsHandle);
  

    //registerInterface(&positionJointSaturationInterface);

    //pos_array.layout.dim.push_back(std_msgs::MultiArrayDimension());
    //pos_array.layout.dim[0].size = jnt_nb;
    //pos_array.layout.dim[0].stride = 1;
    //pos_array.layout.dim[0].label = "pos";
}

void Quadrus::update(const ros::TimerEvent& e){
    elapsed_time_ = ros::Duration(e.current_real - e.last_real);
    read();
    controller_manager_->update(ros::Time::now(), elapsed_time_);
    write(elapsed_time_);
}  

void Quadrus::read(){
    for(int i=0;i<jnt_nb;i++){
        pos[i] = 0;
        vel[i] = 0;
        eff[i] = 0;
    }
}

void Quadrus::write(ros::Duration elapsed_time){
    
    //positionJointSaturationInterface.enforceLimits(elapsed_time);
    pos_array.data.clear();
    for(int i=0;i<jnt_nb;i++){
        pos_array.data.push_back(cmd[i]);
    }
    position_pub.publish(pos_array);

}

int main(int argc, char** argv){
    ros::init(argc, argv, "qd_hw_interface_node");
    ros::NodeHandle nh;

    ros::MultiThreadedSpinner spinner(2);

    Quadrus quad(nh);
    spinner.spin();

    return 0;
}