#include "CurseNode.h"

int main(int argc, char**argv)
{	
	
	ros::init(argc,argv,"Curse");
	
	initCurseNode();
	printw("Keyboard control\n");
	
	RosPart rp; //node handle, publisher without advertise
	DataPart dp; //input and twist
	initRosPart(rp);
	
	do{
	
	get_process_input(dp);
	printw("%c:%d\r",dp.input,dp.input);
	rp.publisher.publish(dp.twist);
	refresh();
	
	}while(dp.input!=27);
	
	endwin();
	return 0;
}



