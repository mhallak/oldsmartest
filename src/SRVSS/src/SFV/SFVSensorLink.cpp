/*
 * SFVSensorLink.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#include "SFV/SFVSensorLink.h"

SFVSensorLink::SFVSensorLink(DPGroup *dpGroup):SFVBase(dpGroup)
{
	setStructure();
	init(dpGroup);
}

void SFVSensorLink::setStructure()
{
	m_objectType="SensorLink";
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::sensor_link_i_location_deviation_X,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::sensor_link_i_location_deviation_Y,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::sensor_link_i_location_deviation_Z,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::sensor_link_i_location_deviation_Roll,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::sensor_link_i_location_deviation_Pitch,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::sensor_link_i_location_deviation_Yaw,0));
}

int SFVSensorLink::getId() const {
	return m_Id;
}

void SFVSensorLink::setId(int id) {
	m_Id = id;
}

double SFVSensorLink::getLocationPitchDeviation() const {
	return m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_Pitch)->getResult();
}

void SFVSensorLink::setLocationPitchDeviation(double locationPitchDeviation) {
	m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_Pitch)->setResult(locationPitchDeviation);
}

double SFVSensorLink::getLocationRollDeviation() const {
	return m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_Roll)->getResult();
}

void SFVSensorLink::setLocationRollDeviation(double locationRollDeviation) {
	m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_Roll)->setResult(locationRollDeviation);
}

double SFVSensorLink::getLocationXDeviation() const {
	return m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_X)->getResult();
}

void SFVSensorLink::setLocationXDeviation(double locationXDeviation) {
	m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_X)->setResult(locationXDeviation);
}

double SFVSensorLink::getLocationYawDeviation() const {
	return m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_Yaw)->getResult();
}

void SFVSensorLink::setLocationYawDeviation(double locationYawDeviation) {
	m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_Yaw)->setResult(locationYawDeviation);
}

double SFVSensorLink::getLocationYDeviation() const {
	return m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_Y)->getResult();
}

void SFVSensorLink::setLocationYDeviation(double locationYDeviation) {
	m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_Y)->setResult(locationYDeviation);
}

double SFVSensorLink::getLocationZDeviation() const {
	return m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_Z)->getResult();
}

void SFVSensorLink::setLocationZDeviation(double locationZDeviation) {
	m_objects->at(ScenarioFeatureType::sensor_link_i_location_deviation_Z)->setResult(locationZDeviation);
}

SFVSensorLink::~SFVSensorLink() {
	// TODO Auto-generated destructor stub
}


const std::string& SFVSensorLink::getLinkName() const {
	return m_name;
}

void SFVSensorLink::setLinkName(const std::string& linkName) {
	m_name = linkName;
}
