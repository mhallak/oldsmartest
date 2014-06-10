/*
 * DPObject.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: userws1
 */

#include "SFV/DPObject.h"
#include "utils/NumberSampler.h"

DPObject::DPObject():
m_feature(0),
m_result(0)
{}

DPObject *DPObject::clone()
{
	return new DPObject(m_feature);
}

DPObject::DPObject(ScenarioFeature * feature):
m_feature(feature),
m_result(0)
{}

DPObject::~DPObject() {
	// TODO Auto-generated destructor stub
}

void DPObject::calc()
{
	float res;
	switch(m_feature->get_distType().index())
	{
		case ScenarioFeatureDistributionType::uniform_discrete:
			res= NumberSampler::getInstance().uniformDiscreteDistribution(m_feature->get_dist_param_1(),m_feature->get_dist_param_2());
			break;
		case ScenarioFeatureDistributionType::uniform_continuous:
			res=NumberSampler::getInstance().uniformContinuousDistribution(m_feature->get_dist_param_1(),m_feature->get_dist_param_2());
			break;
		case ScenarioFeatureDistributionType::normal_continuous:
			res=NumberSampler::getInstance().normalContinuousDistribution(m_feature->get_dist_param_1(),m_feature->get_dist_param_2());
			break;
		case ScenarioFeatureDistributionType::unknown_distribution:
			throw std::string("unknown_distribution cannot be rolled");
	}
	m_result=res;
}

float DPObject::getResult()
{
	return m_result;
}
void DPObject::setResult(float res)
{
	m_result=res;
}
