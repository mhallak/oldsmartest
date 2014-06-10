/*
 * ScenarioFeatureGroup.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/ScenarioFeatureGroup.h"
#include <string>
#include <stdlib.h>

ScenarioFeatureGroup::ScenarioFeatureGroup() :
m_featureGroupType(ScenarioFeatureGroupType::unknown_feature_group)
{
	m_name="";
	m_features=(new std::vector<ScenarioFeature *>);
}
ScenarioFeatureGroup::ScenarioFeatureGroup(std::string featureType):
	m_featureGroupType(ScenarioFeatureGroupType::parseString(featureType.c_str()))
{
	m_features=(new std::vector<ScenarioFeature *>);
	m_name="";
	set_featureGroupType(ScenarioFeatureGroupType::parseString(featureType.c_str()));
}

ScenarioFeatureGroup::~ScenarioFeatureGroup()
{
	delete m_features;
}


ScenarioFeatureGroupType ScenarioFeatureGroup::get_featureGroupType()
{
	return m_featureGroupType;
}
void ScenarioFeatureGroup::set_featureGroupType(ScenarioFeatureGroupType type)
{
	m_featureGroupType=type;
}

std::string ScenarioFeatureGroup::get_name()
{
	return m_name;
}

void ScenarioFeatureGroup::set_name(std::string name)
{
	m_name=name;
}

std::vector<ScenarioFeature*> * ScenarioFeatureGroup::get_features()
{
	return m_features;
}

void ScenarioFeatureGroup::addFeature(ScenarioFeature* feature)
{
	m_features->push_back(feature);
}

