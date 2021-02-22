#include <qd_control/qd_hw_interface.h>

Quadrus::Quadrus(ros::NodeHandle& nh): nh_(nh){

    init();

    controller_manager_.reset(new controller_manager::ControllerManager(this, nh_));

    loop_hz_ = 10;
    ros::Duration update_freq = ros::Duration(1.0/loop_hz_);

    qd_control_loop_ = nh_.createTimer(update_freq, &Quadrus::update, this);

    position_pub = nh.advertise<std_msgs::Float64>("joint_positions", 1000);
}   
                                                   
Quadrus::~Quadrus(){
}   

void Quadrus::init(){
    for(int i=0;i<jnt_nb;i++){
        hardware_interface::JointStateHandle jointStateHandle("TestJoint", &pos[i], &vel[i], &eff[i]);
        joint_state_interface_.registerHandle(jointStateHandle);

        hardware_interface::JointHandle jointPositionHandle(jointStateHandle, &cmd[i]);
        position_joint_interface_.registerHandle(jointPositionHandle);

        //joint_limits_interface::getJointLimits("JointC", nh_, limits);
        //joint_limits_interface::PositionJointSaturationHandle jointLimitsHandle(jointPositionHandle, limits);
        //positionJointSaturationInterface.registerHandle(jointLimitsHandle);

        registerInterface(&joint_state_interface_);
        registerInterface(&position_joint_interface_);
        //registerInterface(&positionJointSaturationInterface);
    }
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
    
    positionJointSaturationInterface.enforceLimits(elapsed_time);
    std_msgs::Float64 position;
    position.data = 0.1;
    position_pub.publish(position);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "qd_hw_interface_node");
    ros::NodeHandle nh;

    ros::MultiThreadedSpinner spinner(2);

    Quadrus quad(nh);
    spinner.spin();

    return 0;
}