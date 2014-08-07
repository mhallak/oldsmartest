/*
 * SFVObject.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */



#include <iostream>
#include <vector>
#include <map>

#include "SFV/SFVObject.h"
#include "SFDP/ScenarioFeatureType.h"
#include "SFDP/ScenarioFeature.h"
#include "SFDP/ScenarioFeatureGroup.h"

#include "SFV/sfvSubGroup.h"


void SFVObject::initFeaturesMap()
{
	my_features_map = new std::map<ScenarioFeatureType ,ScenarioFeature** >;

    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::object_i_type, & my_object_type ) );
    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::object_i_scaling_factor, & my_scaling_factor));

    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::object_i_location_on_the_X_axis, & my_location_on_the_X_axis));
    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::object_i_location_on_the_Y_axis, & my_location_on_the_Y_axis));
    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::object_i_location_on_the_Z_axis, & my_location_on_the_Z_axis));

    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::object_i_location_Roll,  & my_location_Roll));
    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::object_i_location_Pitch, & my_location_Pitch));
    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::object_i_location_Yaw, & my_location_Yaw));
}


SFVObject::SFVObject(std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV): sfvSubGroup(ScenarioFeatureGroupType::object, parent_SFV)
{
	initFeaturesMap();
	initSubGroup(ScenarioFeatureGroupType::object, ScenarioFeatures_vec, parent_SFV);
	was_rolled_flag = false;

/*
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
*/

}


SFVObject::SFVObject(SFVObject * template_SFVObject):  sfvSubGroup(template_SFVObject->get_Type(), template_SFVObject->get_ParentSFV())
{
	initFeaturesMap();
	cloneSubGroup(template_SFVObject);
	was_rolled_flag = false;
/*
	my_object_type = new ScenarioFeature(template_SFVObject->get_ObjectType());
	my_scaling_factor = new ScenarioFeature(template_SFVObject->get_ScalingFactor());

	my_location_on_the_X_axis = new ScenarioFeature(template_SFVObject->get_LocationOnTheXaxis());
	my_location_on_the_Y_axis = new ScenarioFeature(template_SFVObject->get_LocationOnTheYaxis());
	my_location_on_the_Z_axis = new ScenarioFeature(template_SFVObject->get_LocationOnTheZaxis());

	my_location_Roll = new ScenarioFeature(template_SFVObject->get_LocationRoll());
	my_location_Pitch =  new ScenarioFeature(template_SFVObject->get_LocationPitch());
	my_location_Yaw =  new ScenarioFeature(template_SFVObject->get_LocationYaw());
*/

}


bool SFVObject::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Object) \033[0m"<< std::endl;
		return(false);
	}
	else
	{
		int roll_attemps_limit = 3;
		int roll_attemp=1;
		while (roll_attemp <= roll_attemps_limit)
		{
			rollSubGroupfeatures();
			/*
			my_object_type->roll();
			my_scaling_factor->roll();
			my_location_on_the_X_axis->roll();
			my_location_on_the_Y_axis->roll();
			my_location_on_the_Z_axis->roll();
			my_location_Roll->roll();
			my_location_Pitch->roll();
			my_location_Yaw->roll();
			*/

		if (get_ParentSFV()->rules_check())
			{
			was_rolled_flag = true;
			return(true);
			std::cout << "\033[1;32m Succeed to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		else
			{
			resetSubGroupfeatures();
			/*
			my_object_type = new ScenarioFeature(this->get_ObjectType());
			my_scaling_factor = new ScenarioFeature(this->get_ScalingFactor());
			my_location_on_the_X_axis = new ScenarioFeature(this->get_LocationOnTheXaxis());
			my_location_on_the_Y_axis = new ScenarioFeature(this->get_LocationOnTheYaxis());
			my_location_on_the_Z_axis = new ScenarioFeature(this->get_LocationOnTheZaxis());
			my_location_Roll = new ScenarioFeature(this->get_LocationRoll());
			my_location_Pitch = new ScenarioFeature(this->get_LocationPitch());
			my_location_Yaw = new ScenarioFeature(this->get_LocationYaw());
			*/

			std::cout << "\033[1;35m fail to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		roll_attemp++;
		}
	return(false);
	}
}

TiXmlElement * SFVObject::ToXmlElement(int id)
{
	if (! was_rolled_flag)
	{
		std::cout << "\033[1;31m can not make XML element for SFVObject because it wasn't rolled yet \033[0m"<< std::endl;
		return(0);
	}
	else
	{
		/*
		TiXmlElement * xml_sub_group = new TiXmlElement(get_Type().str());
		xml_sub_group->SetAttribute("ID",std::to_string(id));

		xml_sub_group->LinkEndChild(my_object_type->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(my_scaling_factor->toSFV_XMLElement());

		xml_sub_group->LinkEndChild(my_location_on_the_X_axis->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(my_location_on_the_Y_axis->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(my_location_on_the_Z_axis->toSFV_XMLElement());

		xml_sub_group->LinkEndChild(my_location_Roll->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(my_location_Pitch->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(my_location_Yaw->toSFV_XMLElement());
		return(xml_sub_group);
*/
		return(SubGroupfeaturesToXmlElement(id));
	}
}

SFVObject::~SFVObject()
{

}




