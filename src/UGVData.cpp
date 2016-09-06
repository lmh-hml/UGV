#ifndef UGVDATA_H
#define UGVDATA_H

#include "UGV.h"

/*
	24/8/16: this file defines the data collection and publishing functions.
*/

Control::Control(): linear(0), angular(0),
                          MIN_DIST(40), MAX_DIST(90),MIN_SIDES(50)
{
	Twist_pub=nh.advertise<geometry_msgs::Twist>("RosAria/cmd_vel",1);
	Joy_listener=nh.subscribe<sensor_msgs::Joy>("joy",10, &Control::JoyCallBack,this);
	US_listener=nh.subscribe<ugv::Int16Array>("ultrasonicArray",10, &Control::SonicCallBack,this);
    server.setCallback(boost::bind(&Control::dynamicReconfig, this, _1, _2));
}



//stores joystick reading
void Control::JoyCallBack(const sensor_msgs::Joy::ConstPtr& joy)   //this collects relevant joystick msg
{
    joy_lx=joy->axes[ToFro];
    joy_az=joy->axes[Turn];		
}

//stores ultrsonic sensor readings
void Control::SonicCallBack( const ugv::Int16Array::ConstPtr& ary) //this collects info from front sensors
{
	for( int i=0; i<Sensors::Total; ++i)
	{
		sensor[i]=ary->data[i];
	}
}

//callback when dynamic reconfig happens
void Control::dynamicReconfig(ugv::ControlDistConfig &config, uint32_t level )
{
    MAX_DIST= config.MAX_DIST;
    MIN_DIST= config.MIN_DIST;
    MIN_SIDES= config.MIN_SIDES;
    ROS_INFO( "Dynamic reconfigured: Max %d, Min %d, Sides %d ", MAX_DIST,MIN_DIST,MIN_SIDES);
}

//takes in control parameters, loads them into the twist msg and publish.
void Control::publishTwist(float linearX, float joylinear ,float angularZ, float joyAngular)
{
     twist.linear.x = linearX * joylinear;
     twist.angular.z= angularZ * joyAngular;
     Twist_pub.publish(twist) ;

    ROS_INFO("\n\n"
		"MAX_DIST|MIN_DIST|MIN_SIDES\n" 
		"%d        %d       %d     \n"
		"FR:  %d            %d,%d  \n"  
		"BK:  %d            %d,%d  \n"
		"SR:  Mid        Left,Right\n"
        "Published state is: LX: %.2f, joy: %.2f , az: %f, joyaz: %f\n"
        "Published: linear %.2f, angular %.2f\n",

	
		MAX_DIST, MIN_DIST, MIN_SIDES,
		sensor[Front],	sensor[FrLeft], sensor[FrRight],
		sensor[Back], sensor[BkLeft], sensor[BkRight],
        linearX, joylinear, angularZ, joyAngular,
        twist.linear.x,  twist.angular.z
    );
}

#endif
