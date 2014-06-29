/*
 * SDFPComponent.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/SFDPComponent.h"
#include <iostream>
#include <sstream>

SFDPComponent::SFDPComponent()
{
	m_featureGroups=new std::vector<ScenarioFeatureGroup*>;
}



SFDPComponent::~SFDPComponent()
{

}


void SFDPComponent::addScenarioFeatureGroup (ScenarioFeatureGroup *feature) throw (std::string)
{
	m_featureGroups->push_back(feature);
}


SFVComponent* SFDPComponent::genSFV(std::string resource_file_path)
{
	SFVComponent * sfvComp=new SFVComponent(resource_file_path);

	std::vector<ScenarioFeatureGroup*>* featureGroups=getFeatureGroups();
	std::vector<ScenarioFeatureGroup*>::iterator it;
	std::vector<ScenarioFeature*>::iterator it2;

	for(it=featureGroups->begin();it!=featureGroups->end();it++)
	{
		std::map<ScenarioFeatureType,DPObject*> *dpMap=new std::map<ScenarioFeatureType,DPObject*>;
		for(it2=(*it)->get_features()->begin();it2!=(*it)->get_features()->end();it2++)
		{
			(*dpMap)[(*it2)->get_featureType()]=(new DPObject(*it2));
		}
		sfvComp->addDPObjects((*it)->get_featureGroupType(),new DPGroup((*it)->get_name(),(*it)->get_featureGroupType(),dpMap));
	}
	return sfvComp;
}

std::vector<ScenarioFeatureGroup*>* SFDPComponent::getFeatureGroups(){
	return m_featureGroups;
}
