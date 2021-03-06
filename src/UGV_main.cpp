#include "UGV.h"
#include <stdio.h>
/*
24/8/16: split up class into Control.h, Controlutil.cpp & ControlData.cpp
 */
 bool alive;
void kill(int sig);

int main(int argc, char** argv)
{
	
	alive=true;
    ros::init(argc,argv,"UGV_main");
	Control jc;
    ros::Rate hertz(20);
    jc.publishTwist(0,0,0,0);
    signal(SIGINT, kill);
 
    do{
        jc.Update();
        ros::spinOnce();
        hertz.sleep();
    }while(alive);
    
    
    jc.publishTwist(0,0,0,0);
    ROS_INFO("Closing");
    ros::shutdown();
    
};

void kill(int sig)
{
	alive=false;
}







