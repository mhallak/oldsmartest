/*
 * SFVpath.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#include <iostream>
#include "SFV/SFVpath.h"
#include "SFV/SFVwp.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeature.h"


SFVpath::SFVpath(std::vector<ScenarioFeature *> * ScenarioFeatures_vec): sfvSubGroup(ScenarioFeatureGroupType::Path)
{
		my_number_of_wp = 0;
		my_wp_template = 0;

		for (ScenarioFeature * feature_it : * ScenarioFeatures_vec )
		{
		 switch (feature_it->get_featureType().value())
		 	 {
		 	 case(ScenarioFeatureType::number_of_way_points) :
		 		my_number_of_wp = new ScenarioFeature(feature_it);
		 		break;
		 	 }
		}

		my_wp_template = new SFVwp(ScenarioFeatures_vec);
		my_PathWPs = new std::vector<SFVwp *>;

		was_rolled_flag = false;

		if ( (my_number_of_wp==0) || (my_wp_template==0) )
			{
			std::cout << "\033[1;31m The Path was no fully defined \033[0m" << std::endl;
			}
}

SFVpath::SFVpath(SFVpath * template_SFVpath): sfvSubGroup(ScenarioFeatureGroupType::Path)
{
	my_number_of_wp = new ScenarioFeature(template_SFVpath->get_NumberOfWPs());
	my_wp_template = new SFVwp(template_SFVpath->get_WpTemplate());

	my_PathWPs = new std::vector<SFVwp *>;
	for (SFVwp * wp_it : * template_SFVpath->get_PathWPs())
	 	 {
		my_PathWPs->push_back(new SFVwp(wp_it));
	 	 }

	was_rolled_flag = false;
}

void SFVpath::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Path) \033[0m"<< std::endl;
	}
	else
	{
		my_number_of_wp->roll();
		SFVwp * wp_i;
		for (int i=1 ; i<=my_number_of_wp->get_RolledValue(); i++)
			{
			wp_i = new SFVwp(my_wp_template);
			wp_i->roll();
			my_PathWPs->push_back(wp_i);
			}
		was_rolled_flag = true;
	}
}

SFVpath::~SFVpath()
{

}

