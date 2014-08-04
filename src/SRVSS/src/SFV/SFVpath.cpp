/*
 * SFVpath.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#include <iostream>
#include <tinyxml.h>

#include "SFV/SFVpath.h"
#include "SFV/SFVwp.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeature.h"


SFVpath::SFVpath(std::vector<ScenarioFeature *> * ScenarioFeatures_vec,  SFV * parent_SFV): sfvSubGroup(ScenarioFeatureGroupType::Path, parent_SFV)
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

		my_wp_template = new SFVwp(ScenarioFeatures_vec, parent_SFV);
		my_PathWPs = new std::vector<SFVwp *>;

		was_rolled_flag = false;

		if ( (my_number_of_wp==0) || (my_wp_template==0) )
			{
			std::cout << "\033[1;31m The Path was no fully defined \033[0m" << std::endl;
			}
}

SFVpath::SFVpath(SFVpath * template_SFVpath): sfvSubGroup(template_SFVpath->get_Type(),template_SFVpath->get_ParentSFV())
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



bool SFVpath::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Path) \033[0m"<< std::endl;
		return(false);
	}
	else
	{
		int roll_attemps_limit = 3;
		int roll_attemp=1;
		bool roll_fail_flag=false;

		while (roll_attemp <= roll_attemps_limit)
		{
			my_number_of_wp->roll();
			SFVwp * wp_i;
			for (int i=1 ; i<=my_number_of_wp->get_RolledValue(); i++)
				{
				wp_i = new SFVwp(my_wp_template);
				if (wp_i->roll())
					{
					my_PathWPs->push_back(wp_i);
					}
				else
					{
					roll_fail_flag=true;
					break;
					}
				}

		if (roll_fail_flag)
			{
			my_number_of_wp = new ScenarioFeature(this->get_NumberOfWPs());
			my_PathWPs = new std::vector<SFVwp *>;
			std::cout << "\033[1;35m fail to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		else
			{
			was_rolled_flag = true;
			std::cout << "\033[1;32m Succeed to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			return(true);
			}
		roll_attemp++;
		}
	return(false);
	}
}









TiXmlElement * SFVpath::ToXmlElement(int id)
{
	if (! was_rolled_flag)
	{
		std::cout << "\033[1;31m can not make XML element for SFVpath because it wasn't rolled yet \033[0m"<< std::endl;
		return(0);
	}
	else
	{
		TiXmlElement * xml_sub_group = new TiXmlElement(get_Type().str());
		xml_sub_group->SetAttribute("ID",std::to_string(id));

		int id=1;
		for (SFVwp * wp_it : * get_PathWPs())
		{
			xml_sub_group->LinkEndChild(wp_it->ToXmlElement(id));
			id++;
		}

		return(xml_sub_group);
	}
}

SFVpath::~SFVpath()
{

}

