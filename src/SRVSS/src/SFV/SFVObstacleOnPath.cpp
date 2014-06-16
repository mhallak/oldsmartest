/*
 * SFVObject.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#include "SFV/SFVObstacleOnPath.h"

SFVObstacleOnPath::SFVObstacleOnPath(DPGroup* dpGroup): SFVBase(dpGroup)
{
	setStructure();
	init(dpGroup);
}

void SFVObstacleOnPath::setStructure()
{
	m_objectType="ObstacleOnPath";
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::obstacle_on_path_i_type,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::obstacle_on_path_i_location_along_the_path,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::obstacle_on_path_i_location_perpendicular_to_the_path,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::obstacle_on_path_i_location_on_the_Z_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::obstacle_on_path_i_location_Roll,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::obstacle_on_path_i_location_Pitch,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::obstacle_on_path_i_location_Yaw,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::obstacle_on_path_i_scaling_factor,0));

}


double SFVObstacleOnPath::getPitch() const {
	return m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_Pitch)->getResult();
}

void SFVObstacleOnPath::setPitch(double pitch) {
	m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_Pitch)->setResult(pitch);
}

double SFVObstacleOnPath::getRoll() const {
	return m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_Roll)->getResult();
}

void SFVObstacleOnPath::setRoll(double roll) {
	m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_Roll)->setResult(roll);
}

double SFVObstacleOnPath::getScale() const {
	return m_objects->at(ScenarioFeatureType::obstacle_on_path_i_scaling_factor)->getResult();
}

void SFVObstacleOnPath::setScale(double scale) {
	m_objects->at(ScenarioFeatureType::obstacle_on_path_i_scaling_factor)->setResult(scale);
}

int SFVObstacleOnPath::getType() const {
	return m_objects->at(ScenarioFeatureType::obstacle_on_path_i_type)->getResult();
}

void SFVObstacleOnPath::setType(int type) {
	m_objects->at(ScenarioFeatureType::obstacle_on_path_i_type)->setResult(type);
}

double SFVObstacleOnPath::getAlong() const {
	return m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_along_the_path)->getResult();
}

void SFVObstacleOnPath::setAlong(double x) {
	 m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_along_the_path)->setResult(x);
}

double SFVObstacleOnPath::getPerpendicular() const {
	return  m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_perpendicular_to_the_path)->getResult();
}

void SFVObstacleOnPath::setPerpendicular(double y) {
	 m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_perpendicular_to_the_path)->setResult(y);
}

double SFVObstacleOnPath::getYaw() const {
	return  m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_Yaw)->getResult();
}

void SFVObstacleOnPath::setYaw(double yaw) {
	m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_Yaw)->setResult(yaw);
}

double SFVObstacleOnPath::getZ() const {
	return m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_on_the_Z_axis)->getResult();
}

void SFVObstacleOnPath::setZ(double z) {
	m_objects->at(ScenarioFeatureType::obstacle_on_path_i_location_on_the_Z_axis)->setResult(z);
}


int SFVObstacleOnPath::getId() const {
	return m_Id;
}

void SFVObstacleOnPath::setId(int id) {
	m_Id = id;
}




SFVObstacleOnPath::~SFVObstacleOnPath()
{
}

