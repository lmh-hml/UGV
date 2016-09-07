#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <curses.h>

ros::NodeHandle nh;
ros::Publisher pub = nh.advertise<

int main(int argc, char** argv)
{

	char* name="KeyNode";
	ros::init(argc,argv,name);
	ros::Rate hertz(100);
	
	initscr();

	
    do
    {

    }
    while(ros::ok());

	return 0;
}

