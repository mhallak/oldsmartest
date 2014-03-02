/*
 * ScenarioFeatureDependecy.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: userws1
 */

#include "SFDP/ScenarioFeatureDependecy.h"
#include "SFDP/ScenarioFeatureDependecyType.h"
#include "SFDP/ScenarioFeatureType.h"


ScenarioFeatureDependecy::ScenarioFeatureDependecy():
m_supportingFeatureType(ScenarioFeatureType::unknown_feature),
m_dependencyType(ScenarioFeatureDependecyType::unknown_dependecy)
{
	m_supportingFeature=0;
}

ScenarioFeatureDependecy::ScenarioFeatureDependecy(std::string val):
m_supportingFeatureType(ScenarioFeatureType::unknown_feature),
m_dependencyType(ScenarioFeatureDependecyType::stringToDependencyType(val))
{
	m_supportingFeature=0;
}

ScenarioFeatureDependecy::ScenarioFeatureDependecy(ScenarioFeatureDependecyType val):
m_supportingFeatureType(ScenarioFeatureType::unknown_feature),
m_dependencyType(val)
{
	m_supportingFeature=0;
}


ScenarioFeatureDependecy::~ScenarioFeatureDependecy() {

}

void ScenarioFeatureDependecy::set_dependecyType(ScenarioFeatureDependecyType val)
{
	m_dependencyType=val;
}

void ScenarioFeatureDependecy::set_supportingFeature(ScenarioFeature * feature)
{
	m_supportingFeature=feature;
}

void ScenarioFeatureDependecy::set_supportingFeatureType(ScenarioFeatureType featureType)
{
	m_supportingFeatureType=featureType;
}


ScenarioFeatureDependecyType ScenarioFeatureDependecy::get_dependecyType()
{
	return m_dependencyType;
}
ScenarioFeature* ScenarioFeatureDependecy::get_supportingFeature()
{
	return m_supportingFeature;
}
ScenarioFeatureType ScenarioFeatureDependecy::get_supportingFeatureType()
{
	return m_supportingFeatureType;
}
