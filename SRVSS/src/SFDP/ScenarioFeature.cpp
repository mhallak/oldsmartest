/*
 * ScenarioFeature.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/ScenarioFeature.h"
#include "SFDP/ScenarioFeatureType.h"
#include "SFDP/ScenarioFeatureDistributionType.h"
#include "SFDP/ScenarioFeatureDependecy.h"
#include <string>
#include <stdlib.h>


ScenarioFeature::ScenarioFeature(std::string featureType):
	m_featureType(ScenarioFeatureType::stringToFeatureType(featureType)),
	m_distType(ScenarioFeatureDistributionType::unknown_distribution),
	m_dist_param_1(0),
	m_dist_param_2(0)
{
	m_featureDependecies=(new std::vector<ScenarioFeatureDependecy *>);
	set_featureType(ScenarioFeatureType::stringToFeatureType(featureType));
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


void ScenarioFeature::addFeatureDependency(ScenarioFeatureDependecy * featureDepend)
{
	m_featureDependecies->push_back(featureDepend);
}


void ScenarioFeature::set_distributionType(ScenarioFeatureDistributionType type)
{
	m_distType=type;
}


std::vector<ScenarioFeatureDependecy *> * ScenarioFeature::get_featureDependecies()
{
	return m_featureDependecies;
}

void ScenarioFeature::set_supportingFeature(ScenarioFeature * suppFeature){
	for(size_t i=0;i<m_featureDependecies->size();i++)
	{
		if(m_featureDependecies->at(i)->get_supportingFeatureType()==suppFeature->get_featureType())
		{
			m_featureDependecies->at(i)->set_supportingFeature(suppFeature);
		}
	}
}

bool ScenarioFeature::isDependentOn(ScenarioFeature * other)
{
	for(size_t i=0;i<m_featureDependecies->size();i++)
	{
		if(m_featureDependecies->at(i)->get_supportingFeatureType()==other->get_featureType())
		{
			return true;
		}
	}
	return false;
}


float ScenarioFeature::get_rolledValue()
{
	return m_rolledValue;
}

bool ScenarioFeature::isCalculated()
{
	return m_isCalculated;
}

void ScenarioFeature::set_rolledValue(float val)
{
	m_rolledValue=val;
	m_isCalculated=true;
}

void ScenarioFeature::reset()
{
	m_isCalculated=false;
}
