/*
 * SFVPlatformPose.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: userws1
 */

#include "SFV/SFVPlatformPose.h"

SFVPlatformPose::SFVPlatformPose(DPGroup * dpGroup): SFVBase(dpGroup)
{
	setStructure();
	init(dpGroup);
}


void SFVPlatformPose::setStructure()
{
	m_objectType="PlatformPose";
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::initial_platform_position_on_map_X_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::initial_platform_position_on_map_Y_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::initial_platform_azimut_on_map,0));
}

SFVPlatformPose::~SFVPlatformPose() {
	// TODO Auto-generated destructor stub
}

int SFVPlatformPose::getId() const {
	return m_Id;
}

void SFVPlatformPose::setId(int id) {
	m_Id = id;
}

double SFVPlatformPose::getLocationAzimut() const {
	return m_objects->at(ScenarioFeatureType::initial_platform_azimut_on_map)->getResult();
}

void SFVPlatformPose::setLocationAzimut(double locationAzimut) {
	m_objects->at(ScenarioFeatureType::initial_platform_azimut_on_map)->setResult(locationAzimut);
}

double SFVPlatformPose::getLocationX() const {
	return m_objects->at(ScenarioFeatureType::initial_platform_position_on_map_X_axis)->getResult();
}

void SFVPlatformPose::setLocationX(double locationX) {
	m_objects->at(ScenarioFeatureType::initial_platform_position_on_map_X_axis)->setResult(locationX);
}

double SFVPlatformPose::getLocationY() const {
	return m_objects->at(ScenarioFeatureType::initial_platform_position_on_map_Y_axis)->getResult();
}

void SFVPlatformPose::setLocationY(double locationY) {
	m_objects->at(ScenarioFeatureType::initial_platform_position_on_map_Y_axis)->setResult(locationY);
}

const std::string& SFVPlatformPose::getPlatformName() const {
	return m_name;
}

void SFVPlatformPose::setPlatformName(const std::string& platformName) {
	m_name = platformName;
}



