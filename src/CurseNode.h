#include <ros/ros.h>
#include <stdio.h>
#include <ncurses.h>
#include <geometry_msgs/Twist.h>

/*
	7/9/2016: Keyboard operation with ncurses library
*/

struct RosPart
{
	ros::NodeHandle nh;
	ros::Publisher publisher;
};

struct DataPart
{
	int input;
	geometry_msgs::Twist twist;
};

void initCurseNode();
void initRosPart(RosPart& rospart);
void get_process_input(DataPart& data);



