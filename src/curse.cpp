#include <ros/ros.h>
#include <stdio.h>
#include <ncurses.h>
#include <geometry_msgs/Twist.h>


void doStuff();


int main(int argc, char**argv)
{	

	ros::init(argc,argv,"Curse");
	ros::NodeHandle nh;
	//ros::Subscriber listener;
	ros::Publisher publisher=nh.advertise<geometry_msgs::Twist>("RosAria/cmd_vel",1);
	geometry_msgs::Twist twist;
	initscr();
	raw();   //allows this progrm to process all input, even ctr-c
	//cbreak(); //this simply allows input to be processed without pressing enter
		
	noecho();
	int ch;
	do{
	
	ch=getch();
	refresh();
	
	if(ch==119){twist.linear.x=1;}
	else{ twist.linear.x=0;}
	
	publisher.publish(twist);
	ROS_INFO("Pressed %c",ch);
	printf("\r\n");
	
	}while(ch!=27);
	
	refresh();
	endwin();

	return 0;
}

void doStuff()
{


	

}


