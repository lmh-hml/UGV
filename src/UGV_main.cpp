#include "UGV.h"

/*
24/8/16: split up class into Control.h, Controlutil.cpp & ControlData.cpp
 */

int main(int argc, char** argv)
{
    ros::init(argc,argv,"UGV_main");
	Control jc;
    ros::Rate hertz(20);
    jc.publishTwist(0,0,0,0);
 
    do{
        jc.Update();
        ros::spinOnce();
        hertz.sleep();
    }while(ros::ok());
}





