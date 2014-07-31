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

SFVterraine::SFVterraine(std::vector<ScenarioFeature *> * ScenarioFeatures_vec): sfvSubGroup(ScenarioFeatureGroupType::map)
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


SFVterraine::SFVterraine(SFVterraine * template_SFVterraine): sfvSubGroup(ScenarioFeatureGroupType::map)
{

	topographic_map_index = new ScenarioFeature(template_SFVterraine->get_TopographicMapIndex());

	was_rolled_flag = false;
}



void SFVterraine::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Typographic Map) \033[0m"<< std::endl;
	}
	else
	{
		topographic_map_index->roll();

		was_rolled_flag = true;
	}
}

SFVterraine::~SFVterraine()
{

}



