/*
 * SDFPComponent.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/SDFPComponent.h"
#include <iostream>
#include <sstream>

SDFPComponent::SDFPComponent()
{
	m_sampler=new NumberSampler;
	m_featureGroups=new std::vector<ScenarioFeatureGroup*>;
}



SDFPComponent::~SDFPComponent()
{
	delete m_sampler;
}


void SDFPComponent::addScenarioFeatureGroup (ScenarioFeatureGroup *feature) throw (std::string)
{
	m_featureGroups->push_back(feature);
	/*std::map<ScenarioFeatureType,ScenarioFeature *>::iterator it;
	it=m_features->find(feature->get_featureType());
	if(it != m_features->end())
		throw std::string("multiple instances of the same feature\n");

	m_features->insert(std::pair<ScenarioFeatureType,ScenarioFeature *>(feature->get_featureType(),feature) );*/
}

bool SDFPComponent::sovleDependecies() throw (std::string)
{
	for(size_t j=0;j<m_featureGroups->size();j++)
	{
		//load group features into a hashmap
		std::map<ScenarioFeatureType,ScenarioFeature *> * features=new std::map<ScenarioFeatureType,ScenarioFeature *>;
		std::vector<ScenarioFeature *>::iterator vec_it;
		for(vec_it=m_featureGroups->at(j)->get_features()->begin();vec_it!=m_featureGroups->at(j)->get_features()->end();vec_it++)
		{
			std::map<ScenarioFeatureType,ScenarioFeature *>::iterator it;
			it=features->find((*vec_it)->get_featureType());
			if(it != features->end())
				throw std::string("multiple instances of the same feature in the same group\n");

			features->insert(std::pair<ScenarioFeatureType,ScenarioFeature *>((*vec_it)->get_featureType(),*vec_it) );
		}

		bool flag=true;

		for (std::map<ScenarioFeatureType,ScenarioFeature *>::iterator it1=features->begin();
																			it1!=features->end();
																								++it1)
		{
			for (size_t i=0;i<it1->second->get_featureDependecies()->size();i++)
			{
				std::map<ScenarioFeatureType,ScenarioFeature *>::iterator it;
				it=features->find(it1->second->get_featureDependecies()->at(i)->get_supportingFeatureType());
				if(it != features->end()){
					it1->second->set_supportingFeature(it->second);
				}else
				{
					throw std::string(ScenarioFeatureType::toString(it1->second->get_featureType())+" in group " +m_featureGroups->at(j)->get_name() +" dependencies not met\n");
					flag=false;
					break;
				}
			}
		}
		if(flag==false)
			return false;
	}
	return true;
}


float SDFPComponent::rollForDistType(ScenarioFeatureDistributionType distType,float distParam1,float distParam2)
{
	float res;
	switch(distType._type)
	{
		case ScenarioFeatureDistributionType::uniform_discrete:
			res= m_sampler->uniformDiscreteDistribution(distParam1,distParam2);
			break;
		case ScenarioFeatureDistributionType::uniform_continuous:
			res=m_sampler->uniformContinuousDistribution(distParam1,distParam2);
			break;
		case ScenarioFeatureDistributionType::normal_continuous:
			res=m_sampler->normalContinuousDistribution(distParam1,distParam2);
			break;
		case ScenarioFeatureDistributionType::unknown_distribution:
			throw std::string("unknown_distribution cannot be rolled");
	}
	return res;
}


void SDFPComponent::rollForFeature(ScenarioFeature* feature,std::vector<RolledValue*> *groupFeatures)
{
	int rollingNumber=1;
	float distParam1=feature->get_dist_param_1();
	float distParam2=feature->get_dist_param_2();
	std::stringstream ss;
	if(feature->get_featureDependecies()>0)
	{

		for (std::vector<ScenarioFeatureDependecy*>::iterator iter=
							feature->get_featureDependecies()->begin();
								iter!=feature->get_featureDependecies()->end();
																			++iter)
		{
			if(!(*iter)->get_supportingFeature()->isCalculated())
			{
				rollForFeature((*iter)->get_supportingFeature(),groupFeatures);
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
					throw std::string("unknown feature dependency cannot be handled");
			}
		}
	}
	for(int i=0;i<rollingNumber;i++){
		float res=rollForDistType(feature->get_distType(),feature->get_dist_param_1(),feature->get_dist_param_2());
		feature->set_rolledValue(res);
		RolledValue* result=new RolledValue;
		result->setRollNumber(i);
		result->setValue(res);
		result->setType(feature->get_featureType());
		groupFeatures->push_back(result);
		//sfvComp->addRolledValue(group->get_name(),feature->get_featureType(),res,i);
		//std::cout<<feature->get_featureType()<<"_"<<i<<" value:"<<res<<std::endl;
	}
}

SFVComponent* SDFPComponent::rollDice()
{
	SFVComponent * sfvComp=new SFVComponent;

	if(!sovleDependecies())
	{
		throw std::string("not all feature dependencies are met");
	}

	for (std::vector<ScenarioFeatureGroup*>::iterator group_it=m_featureGroups->begin();
			group_it!=m_featureGroups->end();
			group_it++)
	{

		std::vector<RolledValue*> * groupFeatures=new std::vector<RolledValue*>;

		for (std::vector<ScenarioFeature*>::iterator feature_it=(*group_it)->get_features()->begin();
				feature_it!=(*group_it)->get_features()->end();
				feature_it++)
		{
			(*feature_it)->reset();
		}

		for (std::vector<ScenarioFeature*>::iterator feature_it=(*group_it)->get_features()->begin();
				feature_it!=(*group_it)->get_features()->end();
				feature_it++)
		{
			if(!(*feature_it)->isCalculated())
			{
				rollForFeature((*feature_it),groupFeatures);
			}
		}

		sfvComp->addRolledValues((*group_it),groupFeatures);
	}

	return sfvComp;
}



