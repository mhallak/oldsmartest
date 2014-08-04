/*
 * SFVmass_link.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */


#include <iostream>
#include "SFV/SFVmass_link.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeatureType.h"

#include "SFV/SFV.h"

SFVmass_link::SFVmass_link(std::string MassLinkName ,std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV): sfvSubGroup(ScenarioFeatureGroupType::mass_link_i, parent_SFV)
{
	my_MassLinkName = MassLinkName;

	mass_deviation = 0;
	inertia_deviation_Ixx_component = 0;	inertia_deviation_Iyy_component = 0;	inertia_deviation_Izz_component = 0;
	location_deviation_X = 0;				location_deviation_Y = 0;				location_deviation_Z = 0;
	location_deviation_Roll = 0;			location_deviation_Pitch = 0;			location_deviation_Yaw = 0;

	for (ScenarioFeature * feature_it : * ScenarioFeatures_vec )
	{
	 switch (feature_it->get_featureType().value())
	 	 {
	 	 case(ScenarioFeatureType::mass_link_i_mass_deviation) :
			mass_deviation = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::mass_link_i_inertia_deviation_Ixx_component) :
			inertia_deviation_Ixx_component = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::mass_link_i_inertia_deviation_Iyy_component) :
			inertia_deviation_Iyy_component = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::mass_link_i_inertia_deviation_Izz_component) :
			inertia_deviation_Izz_component = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::mass_link_i_location_deviation_X) :
			location_deviation_X = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::mass_link_i_location_deviation_Y) :
			location_deviation_Y = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::mass_link_i_location_deviation_Z) :
			location_deviation_Z = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::mass_link_i_location_deviation_Roll) :
			location_deviation_Roll = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::mass_link_i_location_deviation_Pitch) :
			location_deviation_Pitch = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::mass_link_i_location_deviation_Yaw) :
			location_deviation_Yaw = new ScenarioFeature(feature_it);
	 		break;
	 	 }
	 }

	was_rolled_flag = false;

	if (  (my_MassLinkName=="") || (mass_deviation==0) ||
		  (inertia_deviation_Ixx_component==0) || (inertia_deviation_Iyy_component==0) || (inertia_deviation_Izz_component==0) ||
		  (location_deviation_X==0) || (location_deviation_Y==0) || (location_deviation_Z==0) ||
		  (location_deviation_Roll==0) || (location_deviation_Pitch==0) || (location_deviation_Yaw==0) )
		{
		std::cout << "\033[1;31m The Mass Link was no fully defined \033[0m" << std::endl;
		}
}


SFVmass_link::SFVmass_link(SFVmass_link * template_SFVmass_link): sfvSubGroup(template_SFVmass_link->get_Type() ,template_SFVmass_link->get_ParentSFV())
{
	my_MassLinkName = template_SFVmass_link->get_Name();

	mass_deviation = new ScenarioFeature(template_SFVmass_link->get_MassDeviation());

	inertia_deviation_Ixx_component = new ScenarioFeature(template_SFVmass_link->get_InertiaDeviationIxxComponent());
	inertia_deviation_Iyy_component = new ScenarioFeature(template_SFVmass_link->get_InertiaDeviationIyyComponent());
	inertia_deviation_Izz_component = new ScenarioFeature(template_SFVmass_link->get_InertiaDeviationIzzComponent());

	location_deviation_X = new ScenarioFeature(template_SFVmass_link->get_LocationDeviationX());
	location_deviation_Y = new ScenarioFeature(template_SFVmass_link->get_LocationDeviationY());
	location_deviation_Z = new ScenarioFeature(template_SFVmass_link->get_LocationDeviationZ());

	location_deviation_Roll = new ScenarioFeature(template_SFVmass_link->get_LocationDeviationRoll());
	location_deviation_Pitch = new ScenarioFeature(template_SFVmass_link->get_LocationDeviationPitch());
	location_deviation_Yaw = new ScenarioFeature(template_SFVmass_link->get_LocationDeviationYaw());

	was_rolled_flag = false;
}


bool SFVmass_link::roll()
{
	int roll_attemps_limit = 3;

	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Mass Link) \033[0m"<< std::endl;
		return(false);
	}
	else
	{
		int roll_attemp=1;
		while (roll_attemp <= roll_attemps_limit)
		{
		mass_deviation->roll();
		inertia_deviation_Ixx_component->roll();
		inertia_deviation_Iyy_component->roll();
		inertia_deviation_Izz_component->roll();
		location_deviation_X->roll();
		location_deviation_Y->roll();
		location_deviation_Z->roll();
		location_deviation_Roll->roll();
		location_deviation_Pitch->roll();
		location_deviation_Yaw->roll();

		if (get_ParentSFV()->rules_check())
			{
			was_rolled_flag = true;
			std::cout << "\033[1;32m Succeed to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			return(true);
			}
		else
			{
			mass_deviation = new ScenarioFeature(this->get_MassDeviation());
			inertia_deviation_Ixx_component = new ScenarioFeature(this->get_InertiaDeviationIxxComponent());
			inertia_deviation_Iyy_component = new ScenarioFeature(this->get_InertiaDeviationIyyComponent());
			inertia_deviation_Izz_component = new ScenarioFeature(this->get_InertiaDeviationIzzComponent());
			location_deviation_X = new ScenarioFeature(this->get_LocationDeviationX());
			location_deviation_Y = new ScenarioFeature(this->get_LocationDeviationY());
			location_deviation_Z = new ScenarioFeature(this->get_LocationDeviationZ());
			location_deviation_Roll = new ScenarioFeature(this->get_LocationDeviationRoll());
			location_deviation_Pitch = new ScenarioFeature(this->get_LocationDeviationPitch());
			location_deviation_Yaw = new ScenarioFeature(this->get_LocationDeviationYaw());
			std::cout << "\033[1;35m fail to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		roll_attemp++;
		}
	return(false);
	}
}

TiXmlElement * SFVmass_link::ToXmlElement(int id)
{
	if (! was_rolled_flag)
	{
		std::cout << "\033[1;31m can not make XML element for SFVmass_link because it wasn't rolled yet \033[0m"<< std::endl;
		return(0);
	}
	else
	{
		TiXmlElement * xml_sub_group = new TiXmlElement(get_Type().str());
		xml_sub_group->SetAttribute("ID",std::to_string(id));
		xml_sub_group->SetAttribute("link_name",my_MassLinkName);

		xml_sub_group->LinkEndChild(mass_deviation->toSFV_XMLElement());

		xml_sub_group->LinkEndChild(inertia_deviation_Ixx_component->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(inertia_deviation_Iyy_component->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(inertia_deviation_Izz_component->toSFV_XMLElement());

		xml_sub_group->LinkEndChild(location_deviation_X->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(location_deviation_Y->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(location_deviation_Z->toSFV_XMLElement());

		xml_sub_group->LinkEndChild(location_deviation_Roll->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(location_deviation_Pitch->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(location_deviation_Yaw->toSFV_XMLElement());

		return(xml_sub_group);
	}
}



SFVmass_link::~SFVmass_link()
{

}



