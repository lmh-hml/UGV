#include "SensorNode.h"

int main(int argc, char** argv)
{
    ros::init(argc,argv,"UGV_main");
	SensorNode jc;
    ros::Rate hertz(20);

 
    do{
        hertz.sleep();
    }while(ros::ok());
}





