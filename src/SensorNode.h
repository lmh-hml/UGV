#ifndef SENSORNODE_H
#define SENSORNODE_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <ugv/Int16Array.h>

class SensorNode
{
	public:
		SensorNode();	
		
		void publishThis();
		void checkTimer();
		
	private:
		
		const int NumSensors;
		int16_t* sensors;
		
		ros::NodeHandle nh;
		ros::Subscriber listener;
		ros::Publisher  publisher;
		
		void receivedData(const ugv::Int16Array::ConstPtr& ary);

	
};

SensorNode::SensorNode(): NumSensors(6)
{
	sensors=new int16_t[NumSensors];
	publisher=nh.advertise<geometry_msgs::Twist>("RosAria/cmd_vel",1);
	listener=nh.subscribe<ugv::Int16Array>("ultrasonicArray",10,
	&SensorNode::receivedData,this);
}

void SensorNode::receivedData(const ugv::Int16Array::ConstPtr& ary)
{
	for( int i=0; i<NumSensors; ++i)
	{
		sensors[i]=ary->data[i];
	}
}





#endif


