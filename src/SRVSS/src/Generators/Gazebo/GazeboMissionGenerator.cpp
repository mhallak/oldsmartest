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


GazeboMissionGenerator::GazeboMissionGenerator() {
	m_terrainAnalyzer=new TerrainAnalyzer;

}

GazeboMissionGenerator::~GazeboMissionGenerator() {
	// TODO Auto-generated destructor stub
}

float GazeboMissionGenerator::getLastYawPose() const {
	return m_last_yaw_pose;
}

void GazeboMissionGenerator::setLastYawPose(float lastYawPose) {
	m_last_yaw_pose = lastYawPose;
}

const std::string& GazeboMissionGenerator::getLastPlatformName() const {
	return m_last_platform_name;
}

void GazeboMissionGenerator::setLastPlatformName(
		const std::string& lastPlatformName) {
	m_last_platform_name = lastPlatformName;
}

void GazeboMissionGenerator::generateMission(SFVComponent * sfvcomp,std::string filename, std::string resources_file_path)
{

	std::string terrain = ResourceHandler::getInstance(resources_file_path).getTerrainById(sfvcomp->getTerrains()->at(0)->getTerrainId());
	std::string path = ResourceHandler::getInstance(resources_file_path).getModelsPath();

	m_terrainAnalyzer->loadFile(path+"/"+terrain);


	SFVPlatformPose* platformPose=sfvcomp->getPlatformPoses()->at(0);
	m_last_platform_name=platformPose->getPlatformName();


	std::ofstream file;
	file.open (filename.c_str());
	file<< "PLATFORM" <<std::endl;
	file<< platformPose->getPlatformName() <<std::endl;
	file<< "START"<<std::endl;

	float x,y,z;
	m_terrainAnalyzer->getXYZCoord(platformPose->getLocationX(),platformPose->getLocationY(),x,y,z);
	file<< x <<" "<< y <<" "<< z<< " " <<platformPose->getLocationAzimut() << std::endl;
	float azimut = platformPose->getLocationAzimut();

	m_last_x_pose=x;
	m_last_y_pose=y;
	m_last_z_pose=z;
	m_last_yaw_pose=azimut;

	double plat_init_azi = platformPose->getLocationAzimut();

	BOOST_FOREACH(SFVPath* waypoints,*(sfvcomp->getPaths()))
	{
		file<< "WAYPOINTS"<<std::endl;
		BOOST_FOREACH(SFVWaypoint* waypoint,*(waypoints->m_objects))
		{
			azimut= azimut + waypoint->getRelativeAngle();
			x+=waypoint->getWpIDistanceI()*cos(azimut);
			y+=waypoint->getWpIDistanceI()*sin(azimut);
			file<< x <<" " <<y << " " << waypoint->getWpVelocity() << std::endl;
		}
	}
	file.close();
}

void GazeboMissionGenerator::generateMission_ROBIL2(SFVComponent * sfvComp,std::string fileName, std::string resources_file_path)
{
	std::string path_to_terrain_file_name = ResourceHandler::getInstance(resources_file_path).getTerrainById(sfvComp->getTerrains()->at(0)->getTerrainId());
	std::string path_to_terrain_folder = ResourceHandler::getInstance(resources_file_path).getModelsPath();
	m_terrainAnalyzer->loadFile(path_to_terrain_folder+"/"+path_to_terrain_file_name);

	nav_msgs::Path wp_path;
	geometry_msgs::PoseStamped pose;

	SFVPlatformPose* platformPose=sfvComp->getPlatformPoses()->at(0);
	double plat_init_azi = platformPose->getLocationAzimut();
	float wp_x=0, wp_y=0, wp_z=0;
	//m_terrainAnalyzer->getXYZCoord(platformPose->getLocationX(),platformPose->getLocationY(), wp_x, wp_y, wp_z);

	double azi = plat_init_azi, dis = 0;
	SFVPath* path=sfvComp->getPaths()->at(0);
	for (SFVWaypoint *wp : *(path->m_objects) )
	{
    	azi = azi + wp->getRelativeAngle();
		dis = wp->getWpIDistanceI();
    	wp_x = wp_x + dis*cos(azi);
    	wp_y = wp_y + dis*sin(azi);

		pose.pose.position.x = wp_x;
		pose.pose.position.y = wp_y;

		wp_path.poses.push_back(pose);
	}


	robil_msgs::Path Robil2_path;
	Robil2_path.waypoints = wp_path;

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



void GazeboMissionGenerator::generate(SFVComponent * sfvComp , std::string scenario_folder_url, std::string resource_file_url)
{
	std::string temp = scenario_folder_url+"scenarioMission.txt";
	std::cout << " Producing " << temp << std::endl;

	generateMission(sfvComp, temp ,resource_file_url);
}

float GazeboMissionGenerator::getLastXPose() const {
	return m_last_x_pose;
}

void GazeboMissionGenerator::setLastXPose(float lastXPose) {
	m_last_x_pose = lastXPose;
}

float GazeboMissionGenerator::getLastYPose() const {
	return m_last_y_pose;
}

void GazeboMissionGenerator::setLastYPose(float lastYPose) {
	m_last_y_pose = lastYPose;
}

float GazeboMissionGenerator::getLastZPose() const {
	return m_last_z_pose;
}

void GazeboMissionGenerator::setLastZPose(float lastZPose) {
	m_last_z_pose = lastZPose;
}
