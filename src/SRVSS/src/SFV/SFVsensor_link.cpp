/*
 * SFVsensor_link.cpp
 *
 *  Created on: Aug 5, 2014
 *      Author: userws3
 */


#include <iostream>
#include "SFV/SFVsensor_link.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeatureType.h"

#include "SFV/SFV.h"

SFVsensor_link::SFVsensor_link(std::string SensorLinkName ,std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV): sfvSubGroup(ScenarioFeatureGroupType::sensor_link_i, parent_SFV)
{
	my_SensorLinkName = SensorLinkName;
	location_deviationX = 0; 		location_deviationY = 0; 		location_deviationZ = 0;
	location_deviationRoll = 0;		location_deviationPitch = 0;	location_deviationYaw = 0;

	for (ScenarioFeature * feature_it : * ScenarioFeatures_vec )
	{
	 switch (feature_it->get_featureType().value())
	 	 {
	 	 case(ScenarioFeatureType::sensor_link_i_location_deviation_X) :
			location_deviationX = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::sensor_link_i_location_deviation_Y) :
			location_deviationY = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::sensor_link_i_location_deviation_Z) :
			location_deviationZ = new ScenarioFeature(feature_it);
	 		break;

	 	 case(ScenarioFeatureType::sensor_link_i_location_deviation_Roll) :
			location_deviationRoll = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::sensor_link_i_location_deviation_Pitch) :
			location_deviationPitch = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::sensor_link_i_location_deviation_Yaw) :
			location_deviationYaw = new ScenarioFeature(feature_it);
	 		break;
	 	 }
	 }

	was_rolled_flag = false;

	if ( (my_SensorLinkName=="") ||
		 (location_deviationX==0) || (location_deviationY==0) || (location_deviationZ==0) ||
		 (location_deviationRoll==0) || (location_deviationPitch==0) || (location_deviationYaw==0) )
		{
		std::cout << "\033[1;31m The Sensor Link was no fully defined \033[0m" << std::endl;
		}
}


SFVsensor_link::SFVsensor_link(SFVsensor_link * template_SFVsensor_link): sfvSubGroup(template_SFVsensor_link->get_Type() ,template_SFVsensor_link->get_ParentSFV())
{
	my_SensorLinkName = template_SFVsensor_link->get_Name();

	location_deviationX = new ScenarioFeature(template_SFVsensor_link->get_LocationDeviationX());
	location_deviationY = new ScenarioFeature(template_SFVsensor_link->get_LocationDeviationY());
	location_deviationZ = new ScenarioFeature(template_SFVsensor_link->get_LocationDeviationZ());
	location_deviationRoll = new ScenarioFeature(template_SFVsensor_link->get_LocationDeviationRoll());
	location_deviationPitch = new ScenarioFeature(template_SFVsensor_link->get_LocationDeviationPitch());
	location_deviationYaw = new ScenarioFeature(template_SFVsensor_link->get_LocationDeviationYaw());

	was_rolled_flag = false;
}


bool SFVsensor_link::roll()
{
	int roll_attemps_limit = 3;

	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Sensor Link) \033[0m"<< std::endl;
		return(false);
	}
	else
	{
		int roll_attemp=1;
		while (roll_attemp <= roll_attemps_limit)
		{
			location_deviationX->roll();
			location_deviationY->roll();
			location_deviationZ->roll();
			location_deviationRoll->roll();
			location_deviationPitch->roll();
			location_deviationYaw->roll();

		if (get_ParentSFV()->rules_check())
			{
			was_rolled_flag = true;
			std::cout << "\033[1;32m Succeed to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			return(true);
			}
		else
			{
			location_deviationX = new ScenarioFeature(this->get_LocationDeviationX());
			location_deviationY = new ScenarioFeature(this->get_LocationDeviationY());
			location_deviationZ = new ScenarioFeature(this->get_LocationDeviationZ());
			location_deviationRoll = new ScenarioFeature(this->get_LocationDeviationRoll());
			location_deviationPitch = new ScenarioFeature(this->get_LocationDeviationPitch());
			location_deviationYaw = new ScenarioFeature(this->get_LocationDeviationYaw());

			std::cout << "\033[1;35m fail to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		roll_attemp++;
		}
	return(false);
	}
}

TiXmlElement * SFVsensor_link::ToXmlElement(int id)
{
	if (! was_rolled_flag)
	{
		std::cout << "\033[1;31m can not make XML element for SFVsensor_link because it wasn't rolled yet \033[0m"<< std::endl;
		return(0);
	}
	else
	{
		TiXmlElement * xml_sub_group = new TiXmlElement(get_Type().str());
		xml_sub_group->SetAttribute("ID",std::to_string(id));
		xml_sub_group->SetAttribute("link_name",my_SensorLinkName);

		xml_sub_group->LinkEndChild(location_deviationX->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(location_deviationY->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(location_deviationZ->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(location_deviationRoll->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(location_deviationPitch->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(location_deviationYaw->toSFV_XMLElement());

		return(xml_sub_group);
	}
}



SFVsensor_link::~SFVsensor_link()
{

}




