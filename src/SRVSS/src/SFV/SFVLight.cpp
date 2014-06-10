/*
 * SFVLight.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#include "SFV/SFVLight.h"

SFVLight::SFVLight(DPGroup * dpGroup): SFVBase(dpGroup)
{
	setStructure();
	init(dpGroup);
}

void SFVLight::setStructure()
{
	m_objectType="Light";

	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::light_source_i_type,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::light_source_i_location_on_the_X_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::light_source_i_location_on_the_Y_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::light_source_i_location_on_the_Z_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::light_source_i_direction_on_X_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::light_source_i_direction_on_Y_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::light_source_i_light_cone,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::light_source_i_range,0));
}


double SFVLight::getCone() const {
	return m_objects->at(ScenarioFeatureType::light_source_i_light_cone)->getResult();
}

void SFVLight::setCone(double cone) {
	m_objects->at(ScenarioFeatureType::light_source_i_light_cone)->setResult(cone);
}

double SFVLight::getDirectionX() const {
	return m_objects->at(ScenarioFeatureType::light_source_i_direction_on_X_axis)->getResult();
}

void SFVLight::setDirectionX(double directionX) {
	m_objects->at(ScenarioFeatureType::light_source_i_direction_on_X_axis)->setResult(directionX);
}

double SFVLight::getDirectionY() const {
	return m_objects->at(ScenarioFeatureType::light_source_i_direction_on_Y_axis)->getResult();
}

void SFVLight::setDirectionY(double directionY) {
	m_objects->at(ScenarioFeatureType::light_source_i_direction_on_Y_axis)->setResult(directionY);
}

int SFVLight::getId() const {
	return m_Id;
}

void SFVLight::setId(int id) {
	m_Id = id;
}

double SFVLight::getRange() const {
	return m_objects->at(ScenarioFeatureType::light_source_i_range)->getResult();
}

void SFVLight::setRange(double range) {
	m_objects->at(ScenarioFeatureType::light_source_i_range)->setResult(range);
}

int SFVLight::getType() const {
	return m_objects->at(ScenarioFeatureType::light_source_i_type)->getResult();
}

void SFVLight::setType(int type) {
	m_objects->at(ScenarioFeatureType::light_source_i_type)->setResult(type);
}

double SFVLight::getX() const {
	return m_objects->at(ScenarioFeatureType::light_source_i_location_on_the_X_axis)->getResult();
}

void SFVLight::setX(double x) {
	m_objects->at(ScenarioFeatureType::light_source_i_location_on_the_X_axis)->setResult(x);
}

double SFVLight::getY() const {
	return m_objects->at(ScenarioFeatureType::light_source_i_location_on_the_Y_axis)->getResult();
}

void SFVLight::setY(double y) {
	m_objects->at(ScenarioFeatureType::light_source_i_location_on_the_Y_axis)->setResult(y);
}

double SFVLight::getZ() const {
	return m_objects->at(ScenarioFeatureType::light_source_i_location_on_the_Z_axis)->getResult();
}

void SFVLight::setZ(double z) {
	m_objects->at(ScenarioFeatureType::light_source_i_location_on_the_Z_axis)->setResult(z);
}


SFVLight::~SFVLight() {
	// TODO Auto-generated destructor stub
}

