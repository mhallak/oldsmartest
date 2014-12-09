/*
 * GazeboMissionGenerator.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: userws1
 */

#include "Generators/Gazebo/GazeboMissionGenerator.h"
#include <iostream>
#include <fstream>
#include <Resource/ResourceHandler.h>
#include <boost/foreach.hpp>

#include "std_msgs/String.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/Pose.h"

#include "std_msgs/Time.h"
#include "ros/ros.h"

#include <iostream>
#include <sstream>

#include <rosbag/bag.h>
#include <rosbag/view.h>

//#include "robil_msgs/Path.h"
#include "robil_msgs/AssignNavTask.h"
#include "nav_msgs/Odometry.h"
#include "robil_msgs/AssignMission.h"
#include "robil_msgs/AssignMissionTask.h"

#include "SFV/SFV.h"
#include "SFV/SFVpath.h"
#include "SFV/SFVplatformPose.h"

GazeboMissionGenerator::GazeboMissionGenerator() {

}

GazeboMissionGenerator::~GazeboMissionGenerator() {
	// TODO Auto-generated destructor stub
}


void GazeboMissionGenerator::generateMission(SFV *sfv, std::string fileName)
{
	SFVplatformPose *sfv_PlatPose = (SFVplatformPose*)(sfv->get_SubGroupByFeatureGroupType(ScenarioFeatureGroupType::platform_pose));
	SFVpath *sfv_Path = (SFVpath*)(sfv->get_SubGroupByFeatureGroupType(ScenarioFeatureGroupType::Path));

	std::ofstream file;
	file.open (fileName + ".txt");
	file<< "PLATFORM" <<std::endl;
	file<< "koko" <<std::endl;
	file<< "START"<<std::endl;

	float plat_x = sfv_PlatPose->get_PlatInit_xy()->at('x');
	float plat_y = sfv_PlatPose->get_PlatInit_xy()->at('y');
	file<< plat_x <<" " <<plat_y << " " << std::endl;

	file<< "WAYPOINTS"<<std::endl;
	float x, y;
	for(SFVwp* wp_it : *(sfv_Path->get_PathWPs()))
	{
		x=wp_it->get_WPxy()->at('x');
		y=wp_it->get_WPxy()->at('y');
		file<< x <<" " <<y << " " << 3 << std::endl;
	}
	file.close();
}

void GazeboMissionGenerator::generateMission_ROBIL2(SFV * sfv,std::string fileName)
{
	SFVpath *sfv_Path = (SFVpath*)(sfv->get_SubGroupByFeatureGroupType(ScenarioFeatureGroupType::Path));
	SFVplatformPose *sfv_PlatPose = (SFVplatformPose*)(sfv->get_SubGroupByFeatureGroupType(ScenarioFeatureGroupType::platform_pose));

//	nav_msgs::Path wp_path;
//	geometry_msgs::PoseStamped pose;

	robil_msgs::AssignNavTask robilNavTask;
	nav_msgs::Odometry wp;

	float plat_init_x = sfv_PlatPose->get_PlatInit_xy()->at('x');
	float plat_init_y = sfv_PlatPose->get_PlatInit_xy()->at('y');

	for(SFVwp* wp_it : *(sfv_Path->get_PathWPs()))
	{
/*		pose.pose.position.x = wp_it->get_WPxy()->at('x') - plat_init_x;
		pose.pose.position.y = wp_it->get_WPxy()->at('y') - plat_init_y;
		wp_path.poses.push_back(pose);
	*/

		//wp = new nav_msgs::Odometry();
		wp.pose.pose.position.x = wp_it->get_WPxy()->at('x') - plat_init_x;
		wp.pose.pose.position.y = wp_it->get_WPxy()->at('y') - plat_init_y;
		robilNavTask.waypoints.push_back(wp);
	}
	robilNavTask.task_id= std::to_string(100);


	rosbag::Bag bag;
	bag.open(fileName + ".bag", rosbag::bagmode::Write);

	ros::Time task_play_time(1,0);
	bag.write("/OCU/SMME/NavigationTask",task_play_time,robilNavTask);

	robil_msgs::AssignMission robilMission;
	robilMission.mission_id = std::to_string(101);
	robil_msgs::AssignMissionTask mission_task;
	mission_task.task_id = "100";
	robilMission.tasks.push_back(mission_task);

	ros::Time mission_play_time(2,0);
	bag.write("/OCU/SMME/MissionPlan",mission_play_time,robilMission);

	std_msgs::String play;
	play.data = "/mission/101/StartMission";
	ros::Time play_time(7,0);
	bag.write("/decision_making/events",play_time,play);


	bag.close();
/*
	robil_msgs::Path Robil2_path;
	Robil2_path.waypoints = wp_path;
	Robil2_path.is_heading_defined = false;
	Robil2_path.is_ip_defined = false;

	std::stringstream ss;
	ss<<Robil2_path;
	//std::cout<< ss.str() << std::endl;

	ros::Time play_time(10,0);
	rosbag::Bag bag;
	bag.open(fileName + ".bag", rosbag::bagmode::Write);
	bag.write("/SMME/GlobalPath",play_time,Robil2_path);
	bag.close();


	std::ofstream file;
	file.open(fileName + ".yaml");
	file << ss.str();
	file.close();
	*/
}



void GazeboMissionGenerator::generate(SFV * sfv , std::string scenario_folder_url)
{
	std::string temp = scenario_folder_url+"/scenarioMission";

	std::cout << "\033[1;36m Producing " << temp << ".txt \033[1;36m" << std::endl;
	generateMission(sfv, temp);

	std::cout << "\033[1;36m Producing " << temp << ".bag \033[1;36m" << std::endl;
	generateMission_ROBIL2(sfv, temp);
}

