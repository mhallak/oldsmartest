/*
 * SDFPComponent.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/SDFPComponent.h"
#include "SFDP/ScenarioFeature.h"
#include "utils/NumberSampler.h"
#include <iostream>

SDFPComponent::SDFPComponent()
{
	m_features=new std::map<ScenarioFeatureType,ScenarioFeature*>;
	m_sampler=new NumberSampler;
}



SDFPComponent::~SDFPComponent()
{

}


void SDFPComponent::addScenarioFeature (ScenarioFeature *feature) throw (std::string)
{
	std::map<ScenarioFeatureType,ScenarioFeature *>::iterator it;
	it=m_features->find(feature->get_featureType());
	if(it != m_features->end())
		throw std::string("multiple instances of the same feature\n");

	m_features->insert(std::pair<ScenarioFeatureType,ScenarioFeature *>(feature->get_featureType(),feature) );
}

bool SDFPComponent::sovleDependecies()
{
	bool flag=true;

	for (std::map<ScenarioFeatureType,ScenarioFeature *>::iterator it1=m_features->begin();
																		it1!=m_features->end();
																							++it1)
	{
		for (size_t i=0;i<it1->second->get_featureDependecies()->size();i++)
		{
			std::map<ScenarioFeatureType,ScenarioFeature *>::iterator it;
			it=m_features->find(it1->second->get_featureDependecies()->at(i)->get_supportingFeatureType());
			if(it != m_features->end()){
				it1->second->set_supportingFeature(it->second);
			}else
			{
				flag=false;
				break;
			}
		}
	}
	return flag;
}


float SDFPComponent::rollForDistType(ScenarioFeatureDistributionType distType,float distParam1,float distParam2)
{
	float res;
	switch(distType._type)
	{
		case ScenarioFeatureDistributionType::uniform_int_discrete:
			res= m_sampler->uniformIntDistribution(distParam1,distParam2);
			break;
		case ScenarioFeatureDistributionType::uniform_real_discrete:
			res=m_sampler->uniformRealDistribution(distParam1,distParam2);
			break;
		case ScenarioFeatureDistributionType::unknown_distribution:
			throw std::string("unknown_distribution cannot be rolled");
	}
	return res;
}


void SDFPComponent::rollForFeature(ScenarioFeature* feature)
{
	int rollingNumber=1;
	float distParam1=feature->get_dist_param_1();
	float distParam2=feature->get_dist_param_2();
	if(feature->get_featureDependecies()>0)
	{

		for (std::vector<ScenarioFeatureDependecy*>::iterator iter=
							feature->get_featureDependecies()->begin();
								iter!=feature->get_featureDependecies()->end();
																			++iter)
		{
			if(!(*iter)->get_supportingFeature()->isCalculated())
			{
				rollForFeature((*iter)->get_supportingFeature());
			}
			switch((*iter)->get_dependecyType()._type)
			{
				case ScenarioFeatureDependecyType::roll_number:
					rollingNumber=(*iter)->get_supportingFeature()->get_rolledValue();
					break;
				case ScenarioFeatureDependecyType::upper_bound:
					if(distParam1>distParam2)
					{
						distParam1=std::min((*iter)->get_supportingFeature()->get_rolledValue(),distParam1);
					}
					else
					{
						distParam2=std::min((*iter)->get_supportingFeature()->get_rolledValue(),distParam2);
					}
					break;
				case ScenarioFeatureDependecyType::lower_bound:
					if(distParam1>distParam2)
					{
						distParam2=std::max((*iter)->get_supportingFeature()->get_rolledValue(),distParam2);
					}
					else
					{
						distParam1=std::max((*iter)->get_supportingFeature()->get_rolledValue(),distParam1);
					}
					break;
				case ScenarioFeatureDependecyType::unknown_dependecy:
					throw std::string("unknown feature dependecy cannot be handled");
			}
		}
	}
	for(int i=0;i<rollingNumber;i++){
		float res=rollForDistType(feature->get_distType(),feature->get_dist_param_1(),feature->get_dist_param_2());
		feature->set_rolledValue(res);
		std::cout<<feature->get_featureType()<<"_"<<i<<" value:"<<res<<std::endl;
	}

}
SFVObject * SDFPComponent::rollDice()
{

	if(!sovleDependecies())
	{
		throw std::string("not all feature dependencies are met");
	}

	for (std::map<ScenarioFeatureType,ScenarioFeature *>::iterator it=m_features->begin();
																		it!=m_features->end();
																							++it)
	{
		it->second->reset();
	}

	for (std::map<ScenarioFeatureType,ScenarioFeature *>::iterator it=m_features->begin();
																		it!=m_features->end();
																							++it)
	{
		if(!it->second->isCalculated())
		{
			rollForFeature(it->second);
		}
	}


	return 0;
}



