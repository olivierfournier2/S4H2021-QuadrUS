#include <qd_control/qd_hw_interface.h>

Quadrus::Quadrus(ros::NodeHandle& nh): nh_(nh){ //Initialization list : set nh_ to nh

    init();
    controller_manager_.reset(new controller_manager::ControllerManager(this, nh_));

    //Create a timer to periodically call the update() method
    ros::Duration update_freq = ros::Duration(1.0/LOOP_REFRESH_RATE);
    qd_control_loop_ = nh_.createTimer(update_freq, &Quadrus::update, this);

    //Inform master that the node will be publishing to topic /joint_positions with queue size 1000
    position_pub = nh_.advertise<std_msgs::Float64MultiArray>("joint_positions", 1000);
}   
                                                   
Quadrus::~Quadrus(){
    //delete[] jsHandle;
    //delete[] jpHandle;
    //delete[] jlHandle;
}   

void Quadrus::init(){
        
    for(int i = 0;i<NB_JOINTS;i++){
    
        jsHandle[i] = new hardware_interface::JointStateHandle(("J" + std::to_string(i+1)), &pos[i], &vel[i], &eff[i]);
        joint_state_interface_.registerHandle(*jsHandle[i]);

        jpHandle[i] = new hardware_interface::JointHandle(joint_state_interface_.getHandle(("J" + std::to_string(i+1))), &cmd[i]);
        position_joint_interface_.registerHandle(*jpHandle[i]);

        getJointLimits(("J" + std::to_string(i+1)), nh_, *jlimits[i]);

        jlHandle[i] = new joint_limits_interface::PositionJointSaturationHandle(*jpHandle[i], *jlimits[i]);
        position_joint_sat_interface.registerHandle(*jlHandle[i]);
    }

    registerInterface(&joint_state_interface_);
    registerInterface(&position_joint_interface_);
    registerInterface(&position_joint_sat_interface);
}

void Quadrus::update(const ros::TimerEvent& e){
    elapsed_time_ = ros::Duration(e.current_real - e.last_real);
    read();
    controller_manager_->update(ros::Time::now(), elapsed_time_);
    write(elapsed_time_);
}  

void Quadrus::read(){
    for(int i=0;i<NB_JOINTS;i++){
        pos[i] = 0;
        vel[i] = 0;
        eff[i] = 0;
    }
}

void Quadrus::write(ros::Duration elapsed_time){
    
    position_joint_sat_interface.enforceLimits(elapsed_time);
    pos_array.data.clear();
    for(int i=0;i<NB_JOINTS;i++){
        pos_array.data.push_back(cmd[i]);
    }
    position_pub.publish(pos_array);

}

int main(int argc, char** argv){
    ros::init(argc, argv, "qd_hw_interface");
    ros::NodeHandle nh;

    ros::MultiThreadedSpinner spinner(2);

    Quadrus quad(nh);
    spinner.spin();

    return 0;
}