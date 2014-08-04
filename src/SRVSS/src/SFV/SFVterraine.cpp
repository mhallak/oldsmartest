/*
 * SFVterraine.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */



#include <iostream>
#include "SFV/SFVterraine.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeatureType.h"

SFVterraine::SFVterraine(std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV): sfvSubGroup(ScenarioFeatureGroupType::map , parent_SFV)
{

	topographic_map_index = 0;

	for (ScenarioFeature * feature_it : * ScenarioFeatures_vec )
	{
	 switch (feature_it->get_featureType().value())
	 	 {
	 	 case(ScenarioFeatureType::topographic_map) :
		topographic_map_index = new ScenarioFeature(feature_it);
	 		break;
	 	 }
	 }

	was_rolled_flag = false;

	if (topographic_map_index==0)
		{
		std::cout << "\033[1;31m The Typographic Map was no fully defined \033[0m" << std::endl;
		}
}


SFVterraine::SFVterraine(SFVterraine * template_SFVterraine): sfvSubGroup(template_SFVterraine->get_Type(), template_SFVterraine->get_ParentSFV())
{

	topographic_map_index = new ScenarioFeature(template_SFVterraine->get_TopographicMapIndex());

	was_rolled_flag = false;
}


bool SFVterraine::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Typographic Map) \033[0m"<< std::endl;
		return(false);
	}
	else
	{
		int roll_attemps_limit = 3;
		int roll_attemp=1;
		while (roll_attemp <= roll_attemps_limit)
		{
			topographic_map_index->roll();

		if (get_ParentSFV()->rules_check())
			{
			was_rolled_flag = true;
			std::cout << "\033[1;32m Succeed to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			return(true);
			}
		else
			{
			topographic_map_index = new ScenarioFeature(this->get_TopographicMapIndex());
			std::cout << "\033[1;35m Fail to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		roll_attemp++;
		}
	return(false);
	}
}

TiXmlElement * SFVterraine::ToXmlElement(int id)
{
	if (! was_rolled_flag)
	{
		std::cout << "\033[1;31m can not make XML element for SFVterraine because it wasn't rolled yet \033[0m"<< std::endl;
		return(0);
	}
	else
	{
		TiXmlElement * xml_sub_group = new TiXmlElement(get_Type().str());
		xml_sub_group->SetAttribute("ID",std::to_string(id));

		xml_sub_group->LinkEndChild(topographic_map_index->toSFV_XMLElement());

		return(xml_sub_group);
	}
}

SFVterraine::~SFVterraine()
{

}



