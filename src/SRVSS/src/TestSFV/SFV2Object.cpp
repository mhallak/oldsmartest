/*
 * SFV2Object.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */



#include <iostream>
#include <vector>
#include "TestSFV/SFV2Object.h"
#include "SFDP/ScenarioFeatureType.h"
#include "SFDP/ScenarioFeature.h"
#include "SFDP/ScenarioFeatureGroup.h"


SFV2Object::SFV2Object(std::vector<ScenarioFeature *> * ScenarioFeatures_vec): sfvSubGroup(ScenarioFeatureGroupType::object)
{
	my_object_type = 0;
	my_scaling_factor = 0;
	my_location_on_the_X_axis = 0;	my_location_on_the_Y_axis = 0;	my_location_on_the_Z_axis = 0;
	my_location_Roll = 0;			my_location_Pitch = 0;			my_location_Yaw = 0;

	for (ScenarioFeature * feature_it : * ScenarioFeatures_vec )
	{
	 switch (feature_it->get_featureType().value())
	 	 {
	 	 case(ScenarioFeatureType::object_i_type) :
			my_object_type = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::object_i_scaling_factor) :
			my_scaling_factor = new ScenarioFeature(feature_it);
	 	 	break;
	 	 case(ScenarioFeatureType::object_i_location_on_the_X_axis) :
			my_location_on_the_X_axis = new ScenarioFeature(feature_it);
	 	 	break;
	 	 case(ScenarioFeatureType::object_i_location_on_the_Y_axis) :
			my_location_on_the_Y_axis = new ScenarioFeature(feature_it);
	 	 	break;
	 	 case(ScenarioFeatureType::object_i_location_on_the_Z_axis) :
			my_location_on_the_Z_axis = new ScenarioFeature(feature_it);
	 	 	break;
	 	 case(ScenarioFeatureType::object_i_location_Roll) :
			my_location_Roll = new ScenarioFeature(feature_it);
	 	 	break;
	 	 case(ScenarioFeatureType::object_i_location_Pitch) :
			my_location_Pitch = new ScenarioFeature(feature_it);
	 	 	break;
	 	 case(ScenarioFeatureType::object_i_location_Yaw) :
			my_location_Yaw = new ScenarioFeature(feature_it);
	 	 	break;

	 	 }
	 }
	was_rolled_flag = false;

	if ( 	(my_object_type==0) || (my_scaling_factor==0) ||
			(my_location_on_the_X_axis == 0) || (my_location_on_the_Y_axis == 0) || (my_location_on_the_Z_axis == 0) ||
			(my_location_Roll == 0) || (my_location_Pitch == 0) || (my_location_Yaw == 0) )
		{
		std::cout << "\033[1;31m The Object was no fully defined \033[0m" << std::endl;
		}
}


SFV2Object::SFV2Object(SFV2Object * template_SFV2Object):  sfvSubGroup(ScenarioFeatureGroupType::object)
{
	my_object_type = new ScenarioFeature(template_SFV2Object->get_ObjectType());
	my_scaling_factor = new ScenarioFeature(template_SFV2Object->get_ScalingFactor());

	my_location_on_the_X_axis = new ScenarioFeature(template_SFV2Object->get_LocationOnTheXaxis());
	my_location_on_the_Y_axis = new ScenarioFeature(template_SFV2Object->get_LocationOnTheYaxis());
	my_location_on_the_Z_axis = new ScenarioFeature(template_SFV2Object->get_LocationOnTheZaxis());

	my_location_Roll = new ScenarioFeature(template_SFV2Object->get_LocationRoll());
	my_location_Pitch =  new ScenarioFeature(template_SFV2Object->get_LocationPitch());
	my_location_Yaw =  new ScenarioFeature(template_SFV2Object->get_LocationYaw());

	was_rolled_flag = false;
}


void SFV2Object::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Object) \033[0m"<< std::endl;
	}
	else
	{
		my_object_type->roll();
		my_scaling_factor->roll();

		my_location_on_the_X_axis->roll();
		my_location_on_the_Y_axis->roll();
		my_location_on_the_Z_axis->roll();

		my_location_Roll->roll();
		my_location_Pitch->roll();
		my_location_Yaw->roll();

		was_rolled_flag = true;
	}

}

SFV2Object::~SFV2Object()
{

}




