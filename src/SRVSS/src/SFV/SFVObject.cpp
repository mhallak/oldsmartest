/*
 * SFVObject.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#include "SFV/SFVObject.h"

SFVObject::SFVObject(DPGroup* dpGroup): SFVBase(dpGroup)
{
	setStructure();
	init(dpGroup);
}

void SFVObject::setStructure()
{
	m_objectType="Object";
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::object_i_type,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::object_i_location_on_the_X_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::object_i_location_on_the_Y_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::object_i_location_on_the_Z_axis,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::object_i_location_Roll,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::object_i_location_Pitch,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::object_i_location_Yaw,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::object_i_scaling_factor,0));
}


double SFVObject::getPitch() const {
	return m_objects->at(ScenarioFeatureType::object_i_location_Pitch)->getResult();
}

void SFVObject::setPitch(double pitch) {
	m_objects->at(ScenarioFeatureType::object_i_location_Pitch)->setResult(pitch);
}

double SFVObject::getRoll() const {
	return m_objects->at(ScenarioFeatureType::object_i_location_Roll)->getResult();
}

void SFVObject::setRoll(double roll) {
	m_objects->at(ScenarioFeatureType::object_i_location_Roll)->setResult(roll);
}

double SFVObject::getScale() const {
	return m_objects->at(ScenarioFeatureType::object_i_scaling_factor)->getResult();
}

void SFVObject::setScale(double scale) {
	m_objects->at(ScenarioFeatureType::object_i_scaling_factor)->setResult(scale);
}

int SFVObject::getType() const {
	return m_objects->at(ScenarioFeatureType::object_i_type)->getResult();
}

void SFVObject::setType(int type) {
	m_objects->at(ScenarioFeatureType::object_i_type)->setResult(type);
}

double SFVObject::getX() const {
	return m_objects->at(ScenarioFeatureType::object_i_location_on_the_X_axis)->getResult();
}

void SFVObject::setX(double x) {
	 m_objects->at(ScenarioFeatureType::object_i_location_on_the_X_axis)->setResult(x);
}

double SFVObject::getY() const {
	return  m_objects->at(ScenarioFeatureType::object_i_location_on_the_Y_axis)->getResult();
}

void SFVObject::setY(double y) {
	 m_objects->at(ScenarioFeatureType::object_i_location_on_the_Y_axis)->setResult(y);
}

double SFVObject::getYaw() const {
	return  m_objects->at(ScenarioFeatureType::object_i_location_Yaw)->getResult();
}

void SFVObject::setYaw(double yaw) {
	m_objects->at(ScenarioFeatureType::object_i_location_Yaw)->setResult(yaw);
}

double SFVObject::getZ() const {
	return m_objects->at(ScenarioFeatureType::object_i_location_on_the_Z_axis)->getResult();
}

int SFVObject::getId() const {
	return m_Id;
}

void SFVObject::setId(int id) {
	m_Id = id;
}

void SFVObject::setZ(double z) {
	m_objects->at(ScenarioFeatureType::object_i_location_on_the_Z_axis)->setResult(z);
}



SFVObject::~SFVObject()
{
}

