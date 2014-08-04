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

#include "robil_msgs/Path.h"

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
	SFVplatformPose *sfv_PlatPose = ((std::vector<SFVplatformPose*> *)sfv->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::platform_pose))->at(0);
	SFVpath *sfv_Path = ((std::vector<SFVpath*> *)sfv->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::Path))->at(0);

	std::ofstream file;
	file.open (fileName + ".txt");
	file<< "PLATFORM" <<std::endl;
	file<< "koko" <<std::endl;
	file<< "START"<<std::endl;

	float plat_x = sfv_PlatPose->get_PlatInit_xy(sfv)->at('x');
	float plat_y = sfv_PlatPose->get_PlatInit_xy(sfv)->at('y');
	file<< plat_x <<" " <<plat_y << " " << std::endl;

	file<< "WAYPOINTS"<<std::endl;
	float x, y;
	for(SFVwp* wp_it : *(sfv_Path->get_PathWPs()))
	{

		x=wp_it->get_WPxy(sfv)->at('x');
		y=wp_it->get_WPxy(sfv)->at('y');
		file<< x <<" " <<y << " " << 3 << std::endl;
	}
	file.close();
}

void GazeboMissionGenerator::generateMission_ROBIL2(SFV * sfv,std::string fileName)
{
	SFVpath *sfv_Path = ((std::vector<SFVpath*> *)sfv->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::Path))->at(0);

	nav_msgs::Path wp_path;
	geometry_msgs::PoseStamped pose;
	for(SFVwp* wp_it : *(sfv_Path->get_PathWPs()))
	{
		pose.pose.position.x = wp_it->get_WPxy(sfv)->at('x');
		pose.pose.position.y = wp_it->get_WPxy(sfv)->at('y');

		wp_path.poses.push_back(pose);
	}


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
}



void GazeboMissionGenerator::generate(SFV * sfv , std::string scenario_folder_url)
{
	std::string temp = scenario_folder_url+"/scenarioMission";

	std::cout << "\033[1;36m Producing " << temp << ".txt \033[1;36m" << std::endl;
	generateMission(sfv, temp);

	std::cout << "\033[1;36m Producing " << temp << ".bag \033[1;36m" << std::endl;
	generateMission_ROBIL2(sfv, temp);
}

