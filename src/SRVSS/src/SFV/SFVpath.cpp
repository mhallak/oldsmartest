/*
 * SFVpath.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#include <iostream>
#include <tinyxml.h>
#include <math.h>

#include "SFV/SFVpath.h"
#include "SFV/SFVwp.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeature.h"


void SFVpath::initFeaturesMap()
{
	std::map<ScenarioFeatureType ,ScenarioFeature** > * my_features_map = get_FeaturesMap();

    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::number_of_way_points, & my_number_of_wp ) );
}


SFVpath::SFVpath(std::vector<ScenarioFeature *> * ScenarioFeatures_vec,  SFV * parent_SFV): sfvSubGroup(ScenarioFeatureGroupType::Path, parent_SFV)
{
	initFeaturesMap();
	initSubGroupFeatures(ScenarioFeatures_vec);

	my_wp_template = new SFVwp(ScenarioFeatures_vec, parent_SFV);
	my_PathWPs = new std::vector<SFVwp *>;

	set_WasRolledFlag(false);
}

SFVpath::SFVpath(SFVpath * template_subGroup): sfvSubGroup(template_subGroup->get_Type(),template_subGroup->get_ParentSFV())
{
	initFeaturesMap();
	cloneSubGroupFeatures(template_subGroup);

	my_wp_template = new SFVwp(template_subGroup->get_WpTemplate());
	my_PathWPs = new std::vector<SFVwp *>;

	set_WasRolledFlag(false);
}



bool SFVpath::roll()
{
	if (get_WasRolledFlag())
	{
		std::cout << "\033[1;31m I already was rolled (I am Path) \033[0m"<< std::endl;
		return(false);
	}
	else
	{
		int roll_attemps_limit = 3;
		int roll_attemp=1;
		bool roll_fail_flag=false;
		my_PathWPs = new std::vector<SFVwp *>;

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
			set_WasRolledFlag(true);
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
	if (! get_WasRolledFlag())
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


float SFVpath::get_PathLength()
{
	SFV* sfv = get_ParentSFV();
	if(! sfv->get_WasRolledFlag())
	{
		std::cout << " can't calculate PathLength as the SFV wasn't fully rolled " << std::endl;
		return 0;
	}

	SFVpath *sfv_path = ((std::vector<SFVpath*> *)sfv->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::Path))->at(0);

	float path_length = 0;

	for(SFVwp *wp_it : *(sfv_path->get_PathWPs()))
		{
		path_length = path_length + wp_it->get_RalativeDistance()->get_RolledValue();
		}

	return(path_length);
}

SFVpath::~SFVpath()
{

}

