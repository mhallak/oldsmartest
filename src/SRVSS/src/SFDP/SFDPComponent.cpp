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



std::vector<SFVComponent*>* SFDPComponent::genSFVs(int num_of_SFVs ,std::string SFVs_destination_folder_path ,std::string resource_file_url)
{
	//SFDPParser SFDPpars;
	//SFDPComponent *sfdpComp=SFDPpars.genSFDPFromFile(SFDP_file_url);

	std::vector<SFVComponent*> * SFVs_vec = new std::vector<SFVComponent*>;


	int success_rollings = 0;
	std::cout << " ############ starting rolling " << num_of_SFVs << " SFVs" << std::endl;
	for (int sfv_i = 1 ; sfv_i <= num_of_SFVs ; sfv_i++)
		{

		std::cout << " ######## generating SFV no " << sfv_i << std::endl;

		SFVComponent * sfvComp = genSFV(resource_file_url);
		sfvComp->init();
		bool sfv_roll_success = sfvComp->calc();

		if (sfv_roll_success)
			{
			SFVs_vec->push_back(sfvComp);
			sfvComp->genFileFromSFV(SFVs_destination_folder_path + "testSFV_" + std::to_string(sfv_i) + ".sfv");
			success_rollings += 1;
			}
		std::cout << " ######## rolling of scenario no : " << sfv_i << " success = " << sfv_roll_success << std::endl;
		}
	std::cout << " ########## success in rolling " << success_rollings << "/" << num_of_SFVs << " SFVs" << std::endl;

	return SFVs_vec;
}



SFVComponent* SFDPComponent::genSFV(std::string resource_file_url)
{
	SFVComponent * sfvComp=new SFVComponent(resource_file_url);

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
