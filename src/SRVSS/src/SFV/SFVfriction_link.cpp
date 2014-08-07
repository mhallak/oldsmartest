/*
 * SFVfriction_link.cpp
 *
 *  Created on: Aug 5, 2014
 *      Author: userws3
 */



#include <iostream>
#include "SFV/SFVfriction_link.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeatureType.h"

#include "SFV/SFV.h"

SFVfriction_link::SFVfriction_link(std::string FrictionLinkName ,std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV): sfvSubGroup(ScenarioFeatureGroupType::friction_link_i, parent_SFV)
{
	my_FrictionLinkName = FrictionLinkName;
	friction_deviation = 0;

	for (ScenarioFeature * feature_it : * ScenarioFeatures_vec )
	{
	 switch (feature_it->get_featureType().value())
	 	 {
	 	 case(ScenarioFeatureType::friction_link_friction_deviation) :
			friction_deviation = new ScenarioFeature(feature_it);
	 		break;
	 	 }
	 }

	was_rolled_flag = false;

	if ( (my_FrictionLinkName=="") || (friction_deviation==0) )
		{
		std::cout << "\033[1;31m The Friction Link was no fully defined \033[0m" << std::endl;
		}
}


SFVfriction_link::SFVfriction_link(SFVfriction_link * template_SFVfriction_link): sfvSubGroup(template_SFVfriction_link->get_Type() ,template_SFVfriction_link->get_ParentSFV())
{
	my_FrictionLinkName = template_SFVfriction_link->get_Name();

	friction_deviation = new ScenarioFeature(template_SFVfriction_link->get_FrictionDeviation());

	was_rolled_flag = false;
}


bool SFVfriction_link::roll()
{
	int roll_attemps_limit = 3;

	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Friction Link) \033[0m"<< std::endl;
		return(false);
	}
	else
	{
		int roll_attemp=1;
		while (roll_attemp <= roll_attemps_limit)
		{
		friction_deviation->roll();

		if (get_ParentSFV()->rules_check())
			{
			was_rolled_flag = true;
			std::cout << "\033[1;32m Succeed to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			return(true);
			}
		else
			{
			friction_deviation = new ScenarioFeature(this->get_FrictionDeviation());
			std::cout << "\033[1;35m fail to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		roll_attemp++;
		}
	return(false);
	}
}

TiXmlElement * SFVfriction_link::ToXmlElement(int id)
{
	if (! was_rolled_flag)
	{
		std::cout << "\033[1;31m can not make XML element for SFVfriction_link because it wasn't rolled yet \033[0m"<< std::endl;
		return(0);
	}
	else
	{
		TiXmlElement * xml_sub_group = new TiXmlElement(get_Type().str());
		xml_sub_group->SetAttribute("ID",std::to_string(id));
		xml_sub_group->SetAttribute("link_name",my_FrictionLinkName);

		xml_sub_group->LinkEndChild(friction_deviation->toSFV_XMLElement());

		return(xml_sub_group);
	}
}



SFVfriction_link::~SFVfriction_link()
{

}



