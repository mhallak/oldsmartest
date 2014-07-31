/*
 * SFVwp.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#include <iostream>
#include <vector>
#include "TestSFV/SFVwp.h"
#include "SFDP/ScenarioFeatureType.h"
#include "SFDP/ScenarioFeature.h"
#include "SFDP/ScenarioFeatureGroup.h"


SFVwp::SFVwp(std::vector<ScenarioFeature *> * ScenarioFeatures_vec): sfvSubGroup(ScenarioFeatureGroupType::WayPoint)
{
	my_relative_angle = 0;
	my_relative_distance = 0;

	for (ScenarioFeature * feature_it : * ScenarioFeatures_vec )
	{
	 switch (feature_it->get_featureType().value())
	 	 {
	 	 case(ScenarioFeatureType::wp_i_relative_angle) :
	 		my_relative_angle = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::wp_i_relative_distance) :
	 		my_relative_distance = new ScenarioFeature(feature_it);
	 	 	break;
	 	 }
	 }
	was_rolled_flag = false;

	if ( (my_relative_angle==0) || (my_relative_distance==0) )
		{
		std::cout << "\033[1;31m The WP was no fully defined \033[0m" << std::endl;
		}
}


SFVwp::SFVwp(SFVwp * template_SFVwp): sfvSubGroup(ScenarioFeatureGroupType::WayPoint)
{
	my_relative_angle = new ScenarioFeature(template_SFVwp->get_RalativeAngel());
	my_relative_distance = new ScenarioFeature(template_SFVwp->get_RalativeDistance());
	was_rolled_flag = false;
}


void SFVwp::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am SFVwp) \033[0m"<< std::endl;
	}
	else
	{
		my_relative_angle->roll();
		my_relative_distance->roll();
		was_rolled_flag = true;
	}

}

SFVwp::~SFVwp()
{

}




