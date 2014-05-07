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

void GazeboMissionGenerator::generateMission(SFVComponent * sfvcomp,std::string filename)
{
	std::string terrain = ResourceHandler::getInstance().getTerrainById(sfvcomp->getTerrains()->at(0)->getTerrainId());
	std::string path = ResourceHandler::getInstance().getModelsPath();

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

	file<< "WAYPOINTS"<<std::endl;
	for(std::vector<SFVWaypoint*>::iterator it=sfvcomp->getWaypoints()->begin();
		it!=sfvcomp->getWaypoints()->end();
		it++)
	{
		azimut+=(*it)->getRelativeAngle();
		x+=(*it)->getWpIDistanceI()*cos(azimut);
		y+=(*it)->getWpIDistanceI()*sin(azimut);
		file<< x <<" " <<y << " " << (*it)->getWpVelocity() << std::endl;
	}
	file.close();
}

void GazeboMissionGenerator::generate(SFVComponent * sfvcomp)
{

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
