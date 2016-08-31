#include <ros/ros.h>
#include <fyp/Int16Array.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	ros::init(argc,argv,"rng");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<fyp::Int16Array>("ultracefeceeecesonicArray", 1000);
	ros::Rate loop_rate(5);
	fyp::Int16Array data;
	int MAX=6;
	
	while(ros::ok())
	{
		for(int i=0;i<MAX;i++)
		{
			srand(time(NULL)+rand()%100);
			data.data[i]=rand()%200;
		}
		pub.publish(data);
	}

	return 0;
}

