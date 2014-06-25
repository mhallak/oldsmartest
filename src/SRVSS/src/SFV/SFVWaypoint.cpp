/*
 * SFVWaypoint.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: userws1
 */

#include "SFV/SFVWaypoint.h"

SFVWaypoint::SFVWaypoint(DPGroup * dpGroup): SFVBase(dpGroup)
{
	setStructure();
	init(dpGroup);
}

void SFVWaypoint::setStructure()
{
	m_objectType="Waypoint";
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::wp_i_relative_angle,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::wp_i_relative_distance,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::wp_i_velocity,0));
}


SFVWaypoint::~SFVWaypoint() {
	// TODO Auto-generated destructor stub
}

int SFVWaypoint::getId() const {
	return m_Id;
}

void SFVWaypoint::setId(int id) {
	m_Id = id;
}

float SFVWaypoint::getRelativeAngle() const {
	return m_objects->at(ScenarioFeatureType::wp_i_relative_angle)->getResult();
}

void SFVWaypoint::setRelativeAngle(float relativeAngle) {
	m_objects->at(ScenarioFeatureType::wp_i_relative_angle)->setResult(relativeAngle);
}

float SFVWaypoint::getWpIDistanceI() const {
	return m_objects->at(ScenarioFeatureType::wp_i_relative_distance)->getResult();
}

void SFVWaypoint::setWpIDistanceI(float wpIDistanceI) {
	m_objects->at(ScenarioFeatureType::wp_i_relative_distance)->setResult(wpIDistanceI);
}


float SFVWaypoint::getWpVelocity() const {
	return m_objects->at(ScenarioFeatureType::wp_i_velocity)->getResult();
}

void SFVWaypoint::setWpVelocity(float wpVelocty) {
	m_objects->at(ScenarioFeatureType::wp_i_velocity)->setResult(wpVelocty);
}

