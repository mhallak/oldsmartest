/*
 * ScenarioFeature.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/ScenarioFeature.h"
#include <string>
#include <stdlib.h>


ScenarioFeature::ScenarioFeature(std::string featureType):
	m_featureType(ScenarioFeatureType::parseString(featureType.c_str())),
	m_distType(ScenarioFeatureDistributionType::unknown_distribution),
	m_dist_param_1(0),
	m_dist_param_2(0)
{
}

ScenarioFeature::~ScenarioFeature()
{
}


ScenarioFeatureType ScenarioFeature::ScenarioFeature::get_featureType()
{
	return m_featureType;
}

ScenarioFeatureDistributionType ScenarioFeature::get_distType()
{
	return m_distType;
}

float ScenarioFeature::get_dist_param_1()
{
	return m_dist_param_1;
}

float ScenarioFeature::get_dist_param_2()
{
	return m_dist_param_2;
}



void ScenarioFeature::set_dist_param_1(float val)
{
	m_dist_param_1=val;
}


void ScenarioFeature::set_dist_param_2(float val)
{
	m_dist_param_2=val;
}

void ScenarioFeature::set_featureType(ScenarioFeatureType type)
{
	m_featureType=type;
}


void ScenarioFeature::set_distributionType(ScenarioFeatureDistributionType type)
{
	m_distType=type;
}

