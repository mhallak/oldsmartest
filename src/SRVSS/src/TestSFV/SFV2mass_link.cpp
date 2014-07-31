/*
 * SFV2mass_link.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */


#include <iostream>
#include "TestSFV/SFV2mass_link.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeatureType.h"

SFV2mass_link::SFV2mass_link(std::string MassLinkName ,std::vector<ScenarioFeature *> * ScenarioFeatures_vec): sfvSubGroup(ScenarioFeatureGroupType::mass_link_i)
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


SFV2mass_link::SFV2mass_link(SFV2mass_link * template_SFV2mass_link): sfvSubGroup(ScenarioFeatureGroupType::Path)
{
	my_MassLinkName = template_SFV2mass_link->get_Name();

	mass_deviation = new ScenarioFeature(template_SFV2mass_link->get_MassDeviation());

	inertia_deviation_Ixx_component = new ScenarioFeature(template_SFV2mass_link->get_InertiaDeviationIxxComponent());
	inertia_deviation_Iyy_component = new ScenarioFeature(template_SFV2mass_link->get_InertiaDeviationIyyComponent());
	inertia_deviation_Izz_component = new ScenarioFeature(template_SFV2mass_link->get_InertiaDeviationIzzComponent());

	location_deviation_X = new ScenarioFeature(template_SFV2mass_link->get_LocationDeviationX());
	location_deviation_Y = new ScenarioFeature(template_SFV2mass_link->get_LocationDeviationY());
	location_deviation_Z = new ScenarioFeature(template_SFV2mass_link->get_LocationDeviationZ());

	location_deviation_Roll = new ScenarioFeature(template_SFV2mass_link->get_LocationDeviationRoll());
	location_deviation_Pitch = new ScenarioFeature(template_SFV2mass_link->get_LocationDeviationPitch());
	location_deviation_Yaw = new ScenarioFeature(template_SFV2mass_link->get_LocationDeviationYaw());

	was_rolled_flag = false;
}



void SFV2mass_link::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Mass Link) \033[0m"<< std::endl;
	}
	else
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

		was_rolled_flag = true;
	}
}

SFV2mass_link::~SFV2mass_link()
{

}



