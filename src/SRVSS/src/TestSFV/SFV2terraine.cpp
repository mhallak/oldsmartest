/*
 * SFV2terraine.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */



#include <iostream>
#include "TestSFV/SFV2terraine.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeatureType.h"

SFV2terraine::SFV2terraine(std::vector<ScenarioFeature *> * ScenarioFeatures_vec): sfvSubGroup(ScenarioFeatureGroupType::map)
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


SFV2terraine::SFV2terraine(SFV2terraine * template_SFV2terraine): sfvSubGroup(ScenarioFeatureGroupType::map)
{

	topographic_map_index = new ScenarioFeature(template_SFV2terraine->get_TopographicMapIndex());

	was_rolled_flag = false;
}



void SFV2terraine::roll()
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

SFV2terraine::~SFV2terraine()
{

}



