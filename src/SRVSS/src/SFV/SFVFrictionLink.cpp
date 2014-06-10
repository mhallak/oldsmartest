/*
 * SFVFrictionLink.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#include "SFV/SFVFrictionLink.h"

SFVFrictionLink::SFVFrictionLink(DPGroup * dpGroup): SFVBase(dpGroup)
{
	setStructure();
	init(dpGroup);
}

void SFVFrictionLink::setStructure()
{
	m_objectType="FrictionLink";
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::friction_link_friction_deviation,0));
}



double SFVFrictionLink::getFrictionDeviation() const {
	return m_objects->at(ScenarioFeatureType::friction_link_friction_deviation)->getResult();
}

void SFVFrictionLink::setFrictionDeviation(double frictionDeviation) {
	m_objects->at(ScenarioFeatureType::friction_link_friction_deviation)->setResult(frictionDeviation);
}

int SFVFrictionLink::getId() const {
	return m_Id;
}

const std::string& SFVFrictionLink::getLinkName() const {
	return m_name;
}

void SFVFrictionLink::setLinkName(const std::string& linkName) {
	m_name = linkName;
}

void SFVFrictionLink::setId(int id) {
	m_Id = id;
}


SFVFrictionLink::~SFVFrictionLink() {
	// TODO Auto-generated destructor stub
}

