/*
 * sick_link_controller.cpp
 *
 *  Created on: Jan 11, 2015
 *      Author: dany
 */

#include "ros/ros.h"
#include <tf/tf.h>
#include "math.h"       // atan2()  sqrt()
#include <cmath>      // std::abs()
#include <algorithm>    // std::min

#include <iostream>
#include <string>

#include <boost/thread/mutex.hpp>

#include "tf/transform_listener.h"
#include "gazebo_msgs/LinkStates.h"

#include "std_msgs/Float64.h"


const float PI = 3.14159;
float upper_bound = PI/4;
float lower_bound = -PI/4;


boost::mutex bounds_mutex;
void amplitude_command_Callback(std_msgs::Float64 amplitude_command)
{
	float new_amp = amplitude_command.data;
	if ( (new_amp < 20) || (new_amp > 80)) // 10 to 120 deg;
	{
	  ROS_ERROR(" Amplitude command exceeded allowed limits !!! ");
	  return;
	}

	bounds_mutex.lock();
		upper_bound = new_amp*PI/180;
		lower_bound = -new_amp*PI/180;
	bounds_mutex.unlock();

	std::cout << " new Amplitude = " << new_amp << std::endl;
}


float direction = 1;
ros::Publisher sick_control_command_pub;
ros::Publisher sick_ang_pub;
tf::TransformListener *listener_ptr;
void sick_link_state_TimerCallback(const ros::TimerEvent&)
{
	tf::StampedTransform sick_link_transform;
		try {
		   listener_ptr->waitForTransform("/body", "sick_link" , ros::Time(0), ros::Duration(1) );
		   listener_ptr->lookupTransform("/body", "sick_link" ,ros::Time(0), sick_link_transform);
			}
		catch (tf::LookupException &ex)
		     {
			  ROS_ERROR(" No sick_link exist !!! ");
		   	  return;
		     }

	float w = sick_link_transform.getRotation().w();
	float z = sick_link_transform.getRotation().z();
	float curante_ang = 0;
	    if ( z > 0 )
	      { curante_ang = 2*acos(w); }
	    else
	      { curante_ang = -2*acos(w); }


	bounds_mutex.lock();
		float UB = upper_bound;
		float LB = lower_bound;
	bounds_mutex.unlock();


	float sick_pose_command = 0;
	if (direction==1)
	{
			float dis = curante_ang - UB;
			if ((std::abs(dis) > PI/180) && (dis<0) )
			{
				sick_pose_command = UB;
			}
			else
			{
				direction = -1;
				sick_pose_command = LB;
			}
	}
	else if (direction==-1)
	{
		    float dis = curante_ang - LB;
			if ((std::abs(dis) > PI/180) && (dis>0) )
			{
				sick_pose_command = LB;
			}
			else
			{
				direction = 1;
				sick_pose_command = UB;
			}
	}


	std::cout << " upper_bound = " << LB*180/PI << " lower_bound = " << UB*180/PI <<  std::endl;
	std::cout << " curante_ang = " << curante_ang*180/PI  << std::endl;
	std::cout << " direction = " << direction << std::endl;

	std_msgs::Float64 sick_ang_msg;
	sick_ang_msg.data = curante_ang*180/PI;
	sick_ang_pub.publish(sick_ang_msg);

	std_msgs::Float64 command_msg;
	command_msg.data = sick_pose_command;
	sick_control_command_pub.publish(command_msg);
}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "sick_controller_node");

  ros::NodeHandle n;

  tf::TransformListener listener(ros::Duration(1),true);
  listener_ptr = &listener;

  ros::Timer sick_link_state_timer = n.createTimer(ros::Duration(0.01), sick_link_state_TimerCallback);
  sick_ang_pub = n.advertise<std_msgs::Float64>("/RobBat/sick/sick_angle", 1000);

  ros::Subscriber amplitude_command_sub = n.subscribe("/RobBat/sick/amplitude_command", 100, amplitude_command_Callback);

  sick_control_command_pub = n.advertise<std_msgs::Float64>("/srvss_bobcat/sick_position_controller/command", 1000);

  ros::spin();

  return 0;
}
