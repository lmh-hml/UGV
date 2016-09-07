#include "CurseNode.h"

void initCurseNode()
{
	initscr();
	raw();
	keypad(stdscr, TRUE);	
	noecho();

}

void initRosPart(RosPart& rospart)
{
	rospart.publisher=rospart.nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);
}

void get_process_input(DataPart& data)
{
	data.input=getch();
	switch(data.input)
	{
		case 119:
		case KEY_UP: data.twist.linear.x=1; break;	
		case 115:
		case KEY_DOWN: data.twist.linear.x=-1; break;
		case 97:
		case KEY_LEFT: data.twist.angular.z=-1; break;
		case 100:
		case KEY_RIGHT: data.twist.angular.z=1; break;
		default: 
			data.twist.linear.x=0;
			data.twist.angular.z=0;
	}
}
